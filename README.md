# multi-thread

the safest way to use QT multi thread base Object

9.27解决多线程带参数信号与槽调用方式是出现的一个问题
问题：
QObject::connect: Cannot queue arguments of type 'XXXX' (Make sure 'XXXX' is registed using qRegisterMetaType().) 
解决：
如果在Qt信号槽中跨线程时使用自定义类型signal/slot来传递，需要注意使用qRegisterMetaType对自定义类型进行注册，最安全的处理方法通过qRegisterMetaType()
将自定义类型进行注册
原因：
当一个signal被放到队列中（queued）时，它的参数(arguments)也会被一起一起放到队列中（queued起来），这就意味着参数在被传送到slot之前需要被拷贝、存储在队列中（queue）中；为了能够在队列中存储这些参数(argument)，Qt需要去construct、destruct、copy这些对象，而为了让Qt知道怎样去作这些事情，参数的类型需要使用qRegisterMetaType来注册
qRegisterMetaType使用方法：
      1、注册位置：在第一次使用此类链接跨线程的signal/slot之前，一般在当前类的构造函数中进行注册（QApplication a(argc, argv)之后）
      2、注册方法：头文件包含：#include <QMetaType>，在main()函数中注册这种类型：qRegisterMetaType<MyClass>("Myclass")
                  如果还希望使用这种类型的引用，可同样要注册：qRegisterMetaType<TextAndNumber>("TextAndNumber&");
                  在class.h   #endif // CLASS_H  之前加上Q_DECLARE_METATYPE(class); 声明   
      3、Myclass的引用类型需单独注册：qRegisterMetaType<MyClass>("Myclass&")
  
  即队列方式使用connect
 
