# 前端

1.LOG(level) <<   
2.initlevel(level)

## level
从小到大包括TRACE,DEBUG,INFO,WARN,ERROR,FATAL

1.initlevel仅应该被全局初始化一次

# 后端
当使用LOG(level)时，实际上是创建一个短暂的synclog类，并调用其stream接受后续的流式输入

## synclog
每个synclog包含一个stream，stream类可用于流式写入内容，synclog的创建需要传入各种log的元信息，例如文件，函数，行号，需要使用c++的宏完成，等级根据用户的LOG(INFO)或LOG(FATAL)分析，还有信息就是线程id，解决办法是为每个线程生成一份程序期间一直存在的tid的string

### 构造
调用add_meta,用于格式化各种元信息以及排序或者颜色

### stream

本质上是一个固定大小的char[]buf的流式接口适配，大小在4096，可接受满足std::to_string的任意类型，对bool，char，char *,std::string,buf类型特化实现

### 析构

将stream的buf中的内容以fwrite(线程安全)输出到stdout中，并且除了LOG(FATAL)其他等级的LOG不会主动刷新fflush

# 线程安全

保证多个线程之间的log高效且安全，同一个线程一定是时间戳小的先于时间戳大的打印，但不同线程中无法保证，例如可能出现thread1 log at 14.25.20 123下一条log为thread2 log at 14.25.20 122
