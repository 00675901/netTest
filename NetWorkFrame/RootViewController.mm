#import "RootViewController.h"
#import "PackDefine.h"
#include "GSDataPool.h"
#include <map>
#include <vector>
#include <stdio.h>

@implementation RootViewController

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    ByteBuffer bb;
    NPacket msg;
    msg.NPCode=1;
    msg.data="中";
    std::cout<<msg.NPCode<<"("<<msg.data<<")"<<std::endl;
    bb.clear();
    bb<<msg;
    std::cout<<(const char*)bb.contents()<<"("<<bb.size()<<")"<<std::endl;
    bb>>msg;
    std::cout<<msg.NPCode<<"("<<msg.data<<")"<<std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    GSDataPool *gsd=GSDataPool::shareInstance();
    std::map<int,int> a;
    std::map<std::string,int> *b;
    typedef std::pair<int,int> tp;
    typedef std::pair<std::string,int> tp2;
    for (int i=0; i<10; i++) {
        a.insert(tp(i,i+1));
        b->insert(tp2("tempsss",i+2));
    }
    
    gsd->postData("tempdata1", &a);
    gsd->postData("tempdata2", b);
    
//    std::map<int,int> *c=(std::map<int,int>*)gsd->getData("tempdata1");
    std::map<std::string,int> *c=(std::map<std::string,int>*)gsd->getData("tempdata2");
    
//    std::map<int,int>::iterator iters;
    std::map<std::string,int>::iterator iters;
    for (iters=c->begin(); iters!=c->end(); ++iters) {
        std::cout<<"key="<<iters->first<<" value="<<iters->second<<std::endl;
    }
    
    
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

@end
