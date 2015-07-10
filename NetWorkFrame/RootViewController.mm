#import "RootViewController.h"
#import "PackDefine.h"
#include <map>
#include <vector>
#include <stdio.h>
#include "NetAppCCJSController.h"

@implementation RootViewController

@synthesize nameLable;

NetAppCCJSController *netMain;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    netMain=new NetAppCCJSController("");
    netMain->bind();

    [super viewDidLoad];
}

-(NSString *)trim:(NSString*)sender{
    NSString* str = [sender stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]]; //前后去空格
    NSString* str2 = [str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];//前后去行
    return str2;
}

-(IBAction)createRoom:(id)sender{
    if ([self trim:nameLable.text]>0) {
        std::string a([nameLable.text UTF8String]);
        netMain->start_server(10, a);
    }
}
-(IBAction)JoinRoom:(id)sender{
    if ([self trim:nameLable.text]>0) {
        std::string a([nameLable.text UTF8String]);
        netMain->start_client(a);
    }
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

@end
