#import <UIKit/UIKit.h>

@interface RootViewController : UIViewController {
    UITextField *nameLable;
}
@property(nonatomic,readwrite) IBOutlet UITextField *nameLable;

-(NSString *)trim:(NSString*)sender;

@end
