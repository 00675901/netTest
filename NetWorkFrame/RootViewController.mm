#import "RootViewController.h"
#import "PackDefine.h"
#include <map>
#include <vector>
#include <stdio.h>
#include "NetAppCCJSController.h"

@implementation RootViewController

@synthesize nameLable;

NetAppCCJSController *netMain;


//1879156928--------192.168.1.112
//1761716416--------192.168.1.105
//1744939200--------192.168.1.104

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    std::string a="测试玩家No.";
    std::string b(GUtils::itos((arc4random()%100)+10));
    a.append(b);
    netMain=new NetAppCCJSController(a);
    netMain->bind();

    [super viewDidLoad];
}

-(NSString *)trim:(NSString*)sender{
    NSString* str = [sender stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]]; //前后去空格
    NSString* str2 = [str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];//前后去行
    return str2;
}

-(IBAction)createRoom:(id)sender{
    netMain->start_server(10);
}
-(IBAction)JoinRoom:(id)sender{
    netMain->start_client();
    netMain->stop_client_service();
    netMain->connect_server(1744939200);
}

-(IBAction)flushTest:(id)sender{
    netMain->get_player_list();
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

@end
