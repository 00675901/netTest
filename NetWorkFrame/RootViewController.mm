#import "RootViewController.h"
#import "PackDefine.h"
#include "GSTestDataPool.h"
#include <map>
#include <vector>
#include <stdio.h>

@implementation RootViewController

GSTestDataPool<std::map<std::string, int>> *tp;
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
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    [super viewDidLoad];
}

-(IBAction)seta1:(id)sender{
//    std::map<std::string,int> *aaa=(std::map<std::string,int>*)gsd->getData("tempdata2");
//    std::cout<<"size1="<<aaa->size()<<std::endl;
//    for (int i=0; i<10; i++) {
//        std::string a="sdvge";
//        a.append(GUtils::itos(i+1));
//        aaa->insert(std::make_pair(a,i));
//    }
}
-(IBAction)geta1:(id)sender{
//    GSDataPool *gsd=GSDataPool::shareInstance();
//    std::map<std::string,int> *c=(std::map<std::string,int>*)gsd->getData("tempdata2");
//    std::map<std::string,int>::iterator iters;
//    std::cout<<"size2="<<c->size()<<std::endl;
//    for (iters=c->begin(); iters!=c->end(); ++iters) {
//        std::cout<<"key="<<iters->first<<" value="<<iters->second<<std::endl;
//    }
}

-(IBAction)seta2:(id)sender{
//    GSDataPool *gsd=GSDataPool::shareInstance();
//    std::map<int,int> *bbb=(std::map<int,int>*)gsd->getData("tempdata1");
//    typedef std::pair<int,int> ccc;
//    for (int i=0; i<10; i++) {
//        bbb->insert(ccc(i,i+2));
//    }
}
-(IBAction)geta2:(id)sender{
//    GSDataPool *gsd=GSDataPool::shareInstance();
//    std::map<int,int> *c=(std::map<int,int>*)gsd->getData("tempdata1");
//    std::map<int,int>::iterator iters;
//    for (iters=c->begin(); iters!=c->end(); ++iters) {
//        std::cout<<"key="<<iters->first<<" value="<<iters->second<<std::endl;
//    }
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

@end
