#include "Cli.hpp"
#include "Output.hpp"
#include "Command.hpp"
#include "Sections/PluginSection.hpp"
#include "Sections/CameraSection.hpp"
#include "Sections/SettingsSection.hpp"

Cli::Cli()
    : SubSection("FullBowody", "FullBowody command line interface")
{
    
}

Cli::~Cli()
{
    
}

void Cli::init(Engine* engine)
{
    this->engine = engine;

    addSection(new PluginSection(this->engine));
    addSection(new CameraSection(this->engine));
    addSection(new SettingsSection(this->engine));

    addSection(CommandFactory::createCommand(
        "exit",
        "Exit the program",
        { },
        [this](std::vector<Argument> args) -> bool {
            this->shouldRun = false;
            return true;
        }
    ));
    
    Output::DrawLine();
}

void Cli::update()
{
    Input::update();

    if (Input::newKey)
        handleKeyPress(Input::keyInfos);
}

void Cli::updateView()
{
    Output::ClearLine();
    Output::ShowComplete(complete(command));
    Output::ShowCommand(command);
    if (shouldRun) Output::DrawLine();
    else std::cout << "\r";
}

void Cli::handleKeyPress(Input::KeyInfos key)
{
    switch (key.type)
    {
    case Input::KeyType::KEY_ALPHA:
        command += key.key;
        updateView();
        break;
    case Input::KeyType::KEY_SPECIAL:
        switch (key.key)
        {
        case Input::Key::KEY_ENTER:
            std::cout << std::endl;
            this->call(command);
            commands[0] = command;
            for (int i = HISTORY_SIZE - 1; i > 0; i--)
                commands[i] = commands[i - 1];
            commandIndex = 0;
            commands[0] = "";
            command = "";
            updateView();
            break;
        case Input::Key::KEY_BACKSPACE:
            if (command.size() > 0)
                command.pop_back();
            commands[0] = command;
            commandIndex = 0;
            updateView();
            break;
        case Input::Key::KEY_TAB:
            command += complete(command);
            commands[0] = command;
            commandIndex = 0;
            updateView();
            break;
        default:
            command += key.key;
            commands[0] = command;
            commandIndex = 0;
            updateView();
            break;
        }
    case Input::KeyType::KEY_CTRL:
        switch (key.key)
        {
        case Input::Key::KEY_DOWN:
            if (commandIndex > 0)
                commandIndex--;
            command = commands[commandIndex];
            updateView();
            break;
        case Input::Key::KEY_UP:
            if (commandIndex < HISTORY_SIZE - 1)
                commandIndex++;
            command = commands[commandIndex];
            updateView();
            break;
        default:
            break;
        }
    default:
        break;
    }
}
