嫌弃官网下载速度太慢的同学，可以点击下面的连接进行下载：

https://mirrors.cloud.tencent.com/gradle/

gradle-wrapper.properties内容如下：

```

distributionBase=GRADLE_USER_HOME
distributionPath=wrapper/dists
zipStoreBase=GRADLE_USER_HOME
zipStorePath=wrapper/dists
distributionUrl=https://mirrors.cloud.tencent.com/gradle/gradle-5.1.1-all.zip`


pluginManagement {
    repositories {
        google {
            content {
                includeGroupByRegex("com\\.android.*")
                includeGroupByRegex("com\\.google.*")
                includeGroupByRegex("androidx.*")
            }
        }
        mavenCentral()
        gradlePluginPortal()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        maven {
            url = uri("https://maven.aliyun.com/repository/public/")
        }
        google()
        mavenCentral()
    }
}

rootProject.name = "Forensics"
include(":app")
 
```