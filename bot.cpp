#include<tgbot/tgbot.h>
#include <boost/algorithm/string/replace.hpp>

std::string findAndReplace (std::string code, std::string character, std::string replaceStr) {
    std::cout << "here 1";
    if (code.find(character) != std::string::npos){
        std::cout << "here";
        boost::replace_all(code, character, replaceStr);
        std::cout << "out";
    }
    return code;
}

std::string run (std::string codeToRun) {
    std::string RUN = "/run ";
    std::string BACKWARD_SLASH = "\\";
    std::string BACKWARD_SLASH_REPLACE = "\\\\";
    std::string QUOTES = "\"";
    std::string QUOTES_REPLACE = "\\\""; 
    std::string result;
    char var[40];


    std::string code = codeToRun.replace(codeToRun.find(RUN),RUN.length(), "");
    code = findAndReplace(codeToRun, BACKWARD_SLASH, BACKWARD_SLASH_REPLACE);
    code = findAndReplace(codeToRun, QUOTES, QUOTES_REPLACE);
    
    
    std::cout << "Final : " << code ;
    
    
    auto codeToExecute = ("./bin/SL \""+ code + "\" 2>&1");
    std::cout << "\n" << codeToExecute << "\n";

    try {
        FILE *fp = popen(codeToExecute.c_str(), "r");
        while (fgets(var, sizeof(var), fp) != NULL) 
            result.append(var);

        pclose(fp);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return result;
    //std::system("")
    /*
    std::string STDIN = "/stdin ";
    int myinput = 0;
    std::for_each(codeToRun.begin(), codeToRun.end(), [&codeToRun](char i){
        std::tolower(i);
    });

    std::string stdin_present
    std::string input = codeToRun.substr(codeToRun.find(STDIN), STDIN.length());
    if (input != std::string::npos) {
        input = input.replace(input.find(STDIN), STDIN.length(), "");
        myinput = 1;
    }
    std::string end = (input != std::string::npos)?codeToRun.length(): input;
    std::string code = codeToRun.substr(0,)
    std::cout << input;
    */
   // return input;
};  

int main() {
    TgBot::Bot bot("2024169074:AAHMeNcw7U2BqjVGS3xKI7y2HDtm5B1Qesk");
    bot.getEvents().onCommand("start",[&bot](TgBot::Message::Ptr mesage){
        bot.getApi().sendMessage(mesage->chat->id,"Result");
    });

    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,"help!!", message->chat->id, message->messageId);
    });
    
    bot.getEvents().onCommand("run", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,run(message->text), message->messageId);
    });

    try
    {
        std::cout << "Bot starting up..." << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {       
            std::cout << "Polling..." << std::endl;
            longPoll.start();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}