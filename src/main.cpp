/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-03 00:25:52
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 00:27:18
 */
#include <iostream>
#include "app/app.h"
#include "basis/defines.h"
using namespace std;


int main(int argc, char const *argv[])
{
    auto app = app::App::GetInstance();
    CHECK_RETURN_RET(!app->Init("test"),-1);
    app->Run();
    app->Shutdown();
    
    return 0;
}
