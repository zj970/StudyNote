# Jetpack Compose

## 初识Jetpack Compose

&emsp;&emsp;Jetpack Compose 是一个用于构建原生 Android UI 的现代工具包。Jetpack Compose 用更少的代码、强大的工具和直观的 Kotlin API 简化并加速了 Android 上的 UI 开发。  
&emsp;&emsp;Jetpack Compose 是围绕着 Composable 函数建立的。这些函数让你通过描述它的形状和数据依赖性，以编程方式定义你的 UI，而不是专注于 UI 的构建过程。要创建一个 Composable 函数，只需在函数名称中添加 @Composable 注解。

### Jetpack Compose——Image使用Coli加载网络图片（包含GIF、SVG）

```
    implementation("io.coil-kt:coil:1.4.0")
    implementation("io.coil-kt:coil-compose:1.4.0")
```
- 示例代码:

```
@Composable
fun imageTest() {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .padding(10.dp)
            .verticalScroll(state = rememberScrollState())
    ) {
        Image(
            modifier = Modifier
                .size(120.dp, 120.dp),
            painter = rememberImagePainter(
                data = "https://img-blog.csdnimg.cn/20210823085620179.jpeg",
                builder = {
                    placeholder(R.drawable.head_icon)//占位图
                    crossfade(true)//淡出效果
                    transformations(CircleCropTransformation())//圆形效果
                }),
            contentDescription = null
        )
        Spacer(modifier = Modifier.padding(2.dp))
        Image(
            modifier = Modifier
                .size(120.dp, 120.dp),
            painter = rememberImagePainter(
                data = "https://img-blog.csdnimg.cn/20210823085620179.jpeg",
                builder = {
                    placeholder(R.drawable.head_icon)//占位图
                    crossfade(true)//淡出效果
                    transformations(RoundedCornersTransformation(0.8f))//圆角效果
                }),
            contentDescription = null
        )
        Spacer(modifier = Modifier.padding(2.dp))
        Image(
            modifier = Modifier
                .size(120.dp, 120.dp),
            painter = rememberImagePainter(
                data = "https://img-blog.csdnimg.cn/20210823085620179.jpeg",
                builder = {
                    placeholder(R.drawable.head_icon)//占位图
                    crossfade(true)//淡出效果
                    transformations(GrayscaleTransformation())//灰度效果
                }),
            contentDescription = null,
            contentScale = ContentScale.Crop
        )
        Spacer(modifier = Modifier.padding(2.dp))
        Image(
            modifier = Modifier
                .size(120.dp, 120.dp),
            painter = rememberImagePainter(
                data = "https://img-blog.csdnimg.cn/20210823085620179.jpeg",
                builder = {
                    placeholder(R.drawable.head_icon)//占位图
                    crossfade(true)//淡出效果
                    transformations(BlurTransformation(LocalContext.current, 0.1f, 2f))//高斯效果
                }),
            contentDescription = null,
            contentScale = ContentScale.Crop
        )
    }
}
```