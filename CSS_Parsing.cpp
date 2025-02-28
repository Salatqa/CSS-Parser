#include "CSS_Parsing.h"

void CSS_Parsing::Parse()
{
    while ((c = getchar()) != EOF)
    {
        if (c == '*' && commands == true && commands_reading == false)
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len + 1] = '\0';
            if (len == 3)
            {
                commands = false;
                buff[0] = '\0';
            }
        }

        else if (commands_reading == false && commands == true && c!='?' && c!=',' && c > ' ')
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len + 1] = '\0';
            commands_reading = true;
        }

        else if (commands == true && commands_reading == true && c != ',' && c != '\n')
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len + 1] = '\0';
        }

        else if (commands == true && commands_reading == true && (c==',' || c=='\n'))
        {
            commands_block++;
            temp = buff;
            if (commands_block == 1) commands_tab[0] = temp;
            else if (commands_block==2) commands_tab[1] = temp;
            else if (commands_block==3 && c=='\n')
            {
                commands_tab[2] = temp;
                commands_reading = false;
            }
            else if(commands_block == 4)
            {
                commands_reading = false;
                commands_block = 0;
            }

            buff[0] = '\0';
            temp = nullptr;

            if (c == '\n' && commands_block == 3)
            {
                CommandsHandling handle;
                handle.HandleCommands(commands_tab, parsing_list);

                commands_tab[0] = NULL;
                commands_tab[1] = NULL;
                commands_tab[2] = NULL;
                commands_block = 0;
            }
        }

        else if (c == '?' && commands == true && commands_block==0)
        {
            std::cout << "?" << " == " << parsing_list.CountSections() << endl;;
        }

        else if (c == '?' && selectors_reading == false && attributes_reading == false && commands == false && will_be_attributes==false)
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len + 1] = '\0';
            if (len == 3)
            {
                commands = true;
                buff[0] = '\0';
            }
        }

        else if (commands==false && selectors_reading==false && attributes_reading == false && c > ' ' && c != ',' && c != '{' && c != '}')
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len+1] = '\0';
            if (will_be_attributes == true)
            {
                attributes_reading = true;
            }
            else selectors_reading = true;
        }

        else if (selectors_reading == true && c != ',' && c>=' ' && c != '{' && c != '}' && c != '\n')
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len+1] = '\0';
        }

        else if (selectors_reading == false && commands == false && c == '{')
        {
            parsing_selectors.AddSelector("GLOBAL_SELECTOR");
            parsing_selectors.list_of_selectors.DecreaseLenght();
            will_be_attributes = true;
        }

        else if (selectors_reading == true && (c == ',' || c == '{'))
        {
            int len = strlen(buff) - 1;
            for (int i = len; i >= 0; i--)
            {
                if (buff[i] <= ' ') buff[i] = '\0';
                else
                {
                    break;
                }
            }

            parsing_selectors.AddSelector(buff);
            buff[0] = '\0';

            selectors_reading = false;

            if (c == '{')
            {
                will_be_attributes = true;
            }
                       
        }

        else if (attributes_reading == true && c != ';' && c != '}')
        {
            int len = strlen(buff);
            buff[len] = c;
            buff[len + 1] = '\0';
        }

        else if (will_be_attributes == true && (c == ';' || c == '}'))
        {
            int len = strlen(buff) - 1;

            if (c == '}' && len == 0) attributes_reading = false;

            if (attributes_reading == true)
            {
                for (int i = len; i >= 0; i--)
                {
                    if (buff[i] <= ' ') buff[i] = '\0';
                    else
                    {
                        break;
                    }
                }

                bool att_value = false;
                bool white_characters = true;
                for (int i = 0; i < strlen(buff); i++)
                {
                    if (buff[i] == ':')
                    {
                        buff2[i] = '\0';
                        att_value = true;
                    }

                    else if (att_value == true)
                    {
                        if (white_characters == true && buff[i] > ' ')
                        {
                            white_characters = false;
                        }

                        if (white_characters == false)
                        {
                            temp += buff[i];
                        }
                    }
                    else
                    {
                        buff2[i] = buff[i];
                    }
                }

                for (int i = strlen(buff2) - 1; i >= 0; i--)
                {
                    if (buff2[i] <= ' ') buff2[i] = '\0';
                    else
                    {
                        break;
                    }
                }

                temp2 = buff2;

                parsing_attributes.AddOrChangeAttribute(temp2, temp);
                buff[0] = '\0';
                buff2[0] = '\0';
                temp = nullptr;
                temp2 = nullptr;

                attributes_reading = false;
            }

            if (c == '}')
            {
                will_be_attributes = false;
                parsing_section.selectors = parsing_selectors;
                parsing_section.attributes = parsing_attributes;
                if (parsing_list.main_list.GetLenght()==0) parsing_list.AddBlock(parsing_block);
                parsing_list.FillBlock(parsing_section);

                parsing_selectors = Selectors();
                parsing_attributes = Attributes();
                parsing_section = Section();
            }
        }
    }
}