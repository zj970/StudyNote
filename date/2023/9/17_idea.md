# IDEA卡顿优化

idea64.vmoptions配置文件

```
-Xms8192m
-Xmx8192m
-XX:NewSize=4096m
-XX:MaxNewSize=4096m
-XX:MaxMetaspaceSize=2048m
-XX:ReservedCodeCacheSize=2048m
-XX:+UseG1GC
-XX:SoftRefLRUPolicyMSPerMB=50
-XX:CICompilerCount=2
-XX:+HeapDumpOnOutOfMemoryError
-XX:-OmitStackTraceInFastThrow
-XX:+IgnoreUnrecognizedVMOptions
-XX:CompileCommand=exclude,com/intellij/openapi/vfs/impl/FilePartNodeRoot,trieDescend
-ea
-Dsun.io.useCanonCaches=false
-Dsun.java2d.metal=true
-Djbr.catch.SIGABRT=true
-Djdk.http.auth.tunneling.disabledSchemes=""
-Djdk.attach.allowAttachSelf=true
-Djdk.module.illegalAccess.silent=true
-Dkotlinx.coroutines.debug=off
-Dsun.tools.attach.tmp.only=true
-Dawt.lock.fair=true
-javaagent:/home/zj970/jetbra/ja-netfilter.jar=jetbrains
--add-opens=java.base/jdk.internal.org.objectweb.asm=ALL-UNNAMED
--add-opens=java.base/jdk.internal.org.objectweb.asm.tree=ALL-UNNAMED
--add-exports=jdk.internal.jvmstat/sun.jvmstat.monitor=ALL-UNNAMED
--add-exports=jdk.internal.jvmstat/sun.jvmstat.monitor.event=ALL-UNNAMED

```

## 解决技巧

- 资源有限的情况下
    - 保存策略： Appearance->System Settings->关闭Save files when...,打开自动保存120S  
    - 增加编译内存，Sttings搜索compiler修改process heap size大小  
    - 内存配置（合理分配资源）下载VisualGC工具 jdk 17要在idea64.vmoptions中配置最后两行  
    - 适当减少，关闭实时扫描功能 
        - idea内置检查
        - 插件扫码

## 插件精选  

 - GsonFormatPlus
 - VisualGC
 - Translation 
 - AndroidLocalize 
 - Generate kotlin data class form json
 - sequence diagram 生成时序图，UML图
 - RestfulTool
 - checkStyle-IDEA 
 - Alibaba Java Conding...
 - MyBatisX
 - Rainbow Brackets