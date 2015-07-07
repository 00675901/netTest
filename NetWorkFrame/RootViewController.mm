#import "RootViewController.h"
#import "PackDefine.h"
#include <map>
#include <vector>
#include <stdio.h>
#include "TestMain.h"

@implementation RootViewController

TestMain tMain;

//GSTestDataPool<std::map<std::string, int>> *tp;
//std::map<std::string,int> tm;
//GSTestDataPool<std::map<std::string,int>> aa(&tm);
//
//std::vector<std::string> tma;
//GSTestDataPool<std::vector<std::string>> bb(&tma);
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    
//    ByteBuffer bb;
//    NPacket msg;
//    msg.NPCode=1;
//    msg.data="中";
//    std::cout<<msg.NPCode<<"("<<msg.data<<")"<<std::endl;
//    bb.clear();
//    bb<<msg;
//    std::cout<<(const char*)bb.contents()<<"("<<bb.size()<<")"<<std::endl;
//    bb>>msg;
//    std::cout<<msg.NPCode<<"("<<msg.data<<")"<<std::endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    tMain.begin();
    [super viewDidLoad];
}

-(IBAction)seta1:(id)sender{
//    std::map<std::string,int> *tmx=aa.getData();
//    tmx->insert(std::make_pair("testtest1", 123));
//    tmx->insert(std::make_pair("testtest2", 456));
//    tmx->insert(std::make_pair("testtest3", 678));
//    tmx->insert(std::make_pair("testtest4", 9));
//    std::map<std::string,int> *aaa=(std::map<std::string,int>*)gsd->getData("tempdata2");
//    std::cout<<"size1="<<aaa->size()<<std::endl;
//    for (int i=0; i<10; i++) {
//        std::string a="sdvge";
//        a.append(GUtils::itos(i+1));
//        aaa->insert(std::make_pair(a,i));
//    }
}
-(IBAction)geta1:(id)sender{
//    std::map<std::string,int> *tmx=aa.getData();
//    std::map<std::string,int>::iterator iters;
//    std::cout<<"size2="<<tmx->size()<<std::endl;
//    for (iters=tmx->begin(); iters!=tmx->end(); ++iters) {
//        std::cout<<"key="<<iters->first<<" value="<<iters->second<<std::endl;
//    }
}

-(IBAction)seta2:(id)sender{
//    std::vector<std::string> *tmx=bb.getData();
//    tmx->push_back("aa");
//    tmx->push_back("bb");
//    tmx->push_back("cc");
}
-(IBAction)geta2:(id)sender{
//    std::vector<std::string> *tmx=bb.getData();
//    std::vector<std::string>::iterator iters;
//    for (iters=tmx->begin(); iters!=tmx->end(); ++iters) {
//        std::cout<<"key="<<*iters<<std::endl;
//    }
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

@end
