#include "Engine.h"

Engine::Engine()
    : isRunning(false), data()
{
}

Engine::~Engine()
{
}

void Engine::run()
{
    // if no active scene, do not run
    if (!loader.getActive())
    {
        printw("No active scene.");
        return;
    }

    // load data from disc
    loadData();

    // initialize all scenes
    loader.init(data);

    // now start running things on the active scene
    Scene *active = loader.getActive();

    // run its enter method now, as the loader will not do that
    active->enter(data);

    bool shouldDrawScreen = true;
    isRunning = true;
    data.initQuit(&isRunning);
    while (isRunning)
    {
        // load next scene?
        if (data.shouldLoadNewScene())
        {
            loader.setNextActive(data.getNextScene());
            loader.loadNext(data);
            active = loader.getActive();

            shouldDrawScreen = true;
        }

        // get input from user
        data.setInput(getch());

        // check for quit key
        if (data.getInput() == 'Q')
        {
            isRunning = false;
        }

        // run input past scene
        shouldDrawScreen = active->input(data) || shouldDrawScreen;

        // update scene
        if (active->update(data) || shouldDrawScreen)
        {
            // draw if update says to draw (update == true)
            active->draw(data);

            data.console.updateScreen();

            shouldDrawScreen = false;
        }
    }

    // errors if don't force quit... oops...

    // so... just force quit
    quit();
}

void Engine::quit()
{
    isRunning = false;

    // clean up
    data.console.reset();
    data.console.updateScreen();

    std::exit(0);
}

void Engine::addScene(std::wstring name, Scene *scene)
{
    loader.addScene(name, scene);
}

void Engine::loadData()
{
    {
        CSVFile blocks = CSVFile("data/blocks.csv");
        data.initBlocks(blocks);
    }

    {
        CSVFile items = CSVFile("data/items.csv");
        data.initItems(items);
    }

    {
        CSVFile colors = CSVFile("data/colors.csv");

        // set colors in console
        int index = 1;
        for (int i = 0; i < colors.getLineCount(); i++)
        {
            auto line = colors.getLine(i);

            // 0 is ID
            // 1 is fg
            // 2 is bg

            int id = std::stoi(line.at(0));

            while (id > index)
            {
                // if an ID was skipped, move it up
                index++;
            }

            // create the color combo
            data.console.createColorCombo(std::stoi(line.at(1)), std::stoi(line.at(2)));
        }
    }

    {
        CSVFile structures = CSVFile("data/structures.csv");

        CSVFile structureVariations = CSVFile("data/structure_variations.csv");

        data.initStructures(structures, structureVariations);
    }

    {
        CSVFile biomes = CSVFile("data/biomes.csv");

        data.initBiomes(biomes);
    }
}
