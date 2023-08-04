# Android Tv 部分页面按键音无效，dispatchKeyEvent分发被拦截

&emsp;&emsp;开始阅读之前，可以简单了解一下这些大佬的文章。  

- [c枫_撸码的日子](https://www.jianshu.com/u/2c5186caa67a)  
    - [Android 按键处理一 （基础知识）](https://www.jianshu.com/p/821b3efbe3a1)
    - [Android 按键处理二 （按键流程之内核曾篇）](https://www.jianshu.com/p/d465008996cd)
    - [Android 按键处理三 （按键流程之framework）](https://www.jianshu.com/p/70769c5f1ffe)
- [空杯的境界](https://blog.csdn.net/benzhujie1245com?type=blog)
    - [Android 按键事件(KeyEvent)的分发机制](https://blog.csdn.net/benzhujie1245com/article/details/89559900)
- [小羊子说](https://juneyang.blog.csdn.net/?type=blog)
    - [Android TV中按键事件和焦点处理总结](https://blog.csdn.net/jun5753/article/details/78665886)
- [圆周率X](https://blog.csdn.net/txksnail?type=blog)
    - [Android dispatchKeyEvent事件分发详解，简单易懂](https://blog.csdn.net/txksnail/article/details/103638638)

## 问题描述：

&emsp;&emsp;接入喇叭，进入应用，突然发现一些页面有系统调用的按键提示音，而有些页面则没有。(最终发现是使用了Scrollview出的bug)

## 问题分析

&emsp;&emsp;既然按键声音没有发出，那首先需要了解一下按键声音是怎么发出的。当用户注册了clickListener，则调用发出playSoundEffect()和响应用户写好的onClick()方法。首先排除系统设置声音无效。可以使用adb命令 <b>adb shell Settings get sound_effects_enabled</b>
查看。（1开启0关闭）既然如此，那只有一个可能，按键被消费了或者被拦截了。先来看看按键按下去，在framework层和应用层发生了什么。

1. 首先触发dispatchKeyEvent，通过上面大佬的文章我们知道，按键起始于DecorView进行分发处理
2. 然后触发onUserInteraction
3. 执行onKeyDown
4. 松开/抬起案件，再次触发dispatchKeyEvent
5. 然后再触发onUserInteraction
6. 再次onKeyUp

&emsp;&emsp;在我的问题中，通过log日志打印发现，没有声音执行的时候并没有执行Activity的onKeyDown，又因为没有写拦截事件(因为所有页面都是继承于一个基类)，锁定在Activity中的dispatchKeyEvent。通过log日志发现，这个方法会执行两次，符合上述的步骤。通过对比发现，没有发出声音的页面是没有成对消费，一次为true一次为false。因为是采用的FragmentActivity，通过Fragment的replace进行交替，而且Fragment不是一次性加载，排除因为焦点的缘故，导致没有按键提示音(子控件也没有焦点消耗按键事件)。

&emsp;&emsp;然后进入终极的Debug环节，通过最终在ViewGroup的dispatchKeyEvent中递归查询当前焦点View为ScollView的子类返回了true。

``` java
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (mInputEventConsistencyVerifier != null) {
            mInputEventConsistencyVerifier.onKeyEvent(event, 1);
        }

        if ((mPrivateFlags & (PFLAG_FOCUSED | PFLAG_HAS_BOUNDS))
                == (PFLAG_FOCUSED | PFLAG_HAS_BOUNDS)) {
            if (super.dispatchKeyEvent(event)) {
                return true;
            }
        } else if (mFocused != null && (mFocused.mPrivateFlags & PFLAG_HAS_BOUNDS)
                == PFLAG_HAS_BOUNDS) {
            if (mFocused.dispatchKeyEvent(event)) {
                return true;
            }
        }

        if (mInputEventConsistencyVerifier != null) {
            mInputEventConsistencyVerifier.onUnhandledEvent(event, 1);
        }
        return false;
    }
```
![KeyEvent分发逻辑图](https://img-blog.csdnimg.cn/20191220211750432.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3R4a3NuYWls,size_16,color_FFFFFF,t_70)

## 问题原因

&emsp;&emsp;就算定位到了这个View产生了事件拦截，但并没有往内容长度上面想。手动屏蔽一个页面，发现原来的主页面有声音了，再对比有声音的页面和无声音的页面，公司的老员工就琢磨出了问题，是这个页面内容超出了屏幕导致的，我一试，在没声音的页面删掉几个加载项，唉？它好了！果断去网上找了几篇文章，发现一篇类似的文章。

- [完美解决Android中的ScrollView嵌套ScrollView滑动冲突问题](https://blog.csdn.net/Ever69/article/details/104315253)

&emsp;&emsp;汗颜，果然家有一老，如有一宝。问题找到了，就是由于焦点管理和事件分发机制的相互作用所致。当按键按下切换的时候，焦点产生了移动，由于内容超出了屏幕。此时按键按下正在尝试滚动，此时的按键事件被视为滚动手势而被拦截。(听同事说，之前他使用自定义的ListView也出现了按键音效被拦截的情况，但是换成了RecylerView便没有了)。

## 解决方案

&emsp;&emsp;解决方法选择了一个简单粗暴的方法，写一个类继承ScrollView重写dispatchKeyEvent方法，当事件被拦截的时候，手动调用播放按键音。如果有大佬有相关的经验，可以评论区讨论一下，非常感谢。

```java
    @Override
    public boolean dispatchKeyEvent(KeyEvent keyEvent) {

        Boolean result = super.dispatchKeyEvent(keyEvent);
        if (keyEvent.getAction() == KeyEvent.ACTION_DOWN && result)
        {
            audioManager.playSoundEffect(AudioManager.FX_FOCUS_NAVIGATION_DOWN);
        }
        return result;
    }
```