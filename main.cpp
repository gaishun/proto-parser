#include <iostream>
#include <google/protobuf/compiler/parser.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include "ErrorCollect_impl.h"

using namespace google::protobuf::compiler;
using namespace google::protobuf::io;
using namespace google::protobuf;
using namespace std;

int main (int argc,char *argv[]){
    int fd = open("/home/gs/Desktop/ali/protobuf/test.proto",O_RDONLY);//打开文件
    ZeroCopyInputStream *zinput = new FileInputStream(fd);//定义文件流
    MockErrorCollector err;
    auto *input = new Tokenizer(zinput, &err);//初始化输出流
    DescriptorPool _pool;

    auto *parser = new Parser();//定义解析
    parser->RecordErrorsTo(&err);
    parser->SetRequireSyntaxIdentifier(false);

    FileDescriptorProto file;
    if (parser->Parse(input,&file)){
        printf("success\n");
    }

    file.set_name("test");//parser but has not name

    const Descriptor* descriptor = file.GetDescriptor();
    const Reflection* reflection = file.GetReflection();
    const FileDescriptor *_file = _pool.BuildFile(file);// dependencies should be in there first.
    const ServiceDescriptor* serivce_name = _file->FindServiceByName("Greeter");
    const Descriptor *message_name = _file->FindMessageTypeByName("Person");
    int count = serivce_name->method_count();
    const MethodDescriptor *method;
//    for(int i=0 ;i <count ; i++) {
//        method = serivce_name->method(i);
//        cout << method->name() << endl;
//        cout << method->DebugString() << endl;
//        cout << method->file() << endl;
//        cout << method->service() << endl;
//        cout << method->client_streaming() << endl;
//        cout << method->full_name() << endl;
//        MethodOptions options = method->options();
//
//        cout << SimpleBtoa(method) << endl;
//    }
    const FieldDescriptor *phnumber = message_name->FindFieldByName("PhoneNumber");
//    cout << _file->DebugString() << endl;
    count = _file->message_type_count();
    cout<< count <<endl;
    for (int i=0;i<count;i++){
        message_name = _file->message_type(i);
        cout<<message_name->name() <<endl;
    }



    return  0;
}