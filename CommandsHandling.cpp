#include "CommandsHandling.h"

void CommandsHandling::HandleCommands(String commands[], MainList &list)
{
    if (commands[1] == "S")
    {
        if (commands[0].ISNumber())
        {
            unsigned long long number = 0;
            number = commands[0].StringToNumber();

            if (commands[2] == "?")
            {
                list.ReturnNumberOfSelectorsOfGivenSection(number);
            }

            else
            {
                if (commands[2].ISNumber())
                {
                    unsigned long long number_2 = 0;
                    number_2 = commands[2].StringToNumber();
                    list.JSelectorInISection(number, number_2);
                }
            }
        }

        else
        {
            if (commands[2] == "?")
            {
                list.SelectorZ(commands[0]);
            }
        }
    }

    else if (commands[1] == "A")
    {
        if (commands[0].ISNumber())
        {
            unsigned long long number = 0;
            number = commands[0].StringToNumber();

            if (commands[2] == "?")
            {
                list.ReturnNumberOfAttributesOfGivenSection(number);
            }

            else
            {
                list.NAttributeInISection(number, commands[2]);
            }
        }

        else
        {
            if (commands[2] == "?")
            {
                list.AttributeN(commands[0]);
            }
        }
    }

    else if (commands[1] == "E")
    {
        list.AttributeNValueforSelectorZ(commands[0], commands[2]);
    }

    else if (commands[1] == "D")
    {
        unsigned long long number = 0;
        if (commands[0].ISNumber())
        {
            number = commands[0].StringToNumber();
        }

        if (commands[2] == "*")
        {
            list.DeleteISection(number, true);
        }

        else
        {
            list.DeleteNAttribute(number, commands[2]);
        }
    }
}