#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <windows.h>

#include <conio.h>

#define VIEW_ROWS 21
#define VIEW_COLS 120

typedef struct component {
    int y, x;
    int width, height = 1;
    char type;
    char * value;
}
        Component;

typedef struct form {
    int number_of_components = 0;
    Component * components;
    char * name;
}
        Form;
//bubble sort components by y of each component . (if ys are equal uses x )
void sort_components(Form f) {
    for (int i = 0; i < f.number_of_components; i++) {
        for (int j = i + 1; j < f.number_of_components; j++) {
            if (f.components[i].y > f.components[j].y) {
                Component c = f.components[i];
                f.components[i] = f.components[j];
                f.components[j] = c;
            } else if (f.components[i].y == f.components[j].y) {
                if (f.components[i].x > f.components[j].x) {
                    Component c = f.components[i];
                    f.components[i] = f.components[j];
                    f.components[j] = c;
                }
            }
        }
    }
}
//skip lines in print_view() function .
void skip_lines() {
    for (int i = 1; i <= 10; i++) {
        printf("\n");
    }
}
//print form
void print_view(Form f, int skip) {
    Form f1;
    //make a copy of input form to avoid changes of input form in sort_components() function .
    f1.number_of_components = f.number_of_components;
    f1.components = (Component * ) malloc(f1.number_of_components * sizeof(Component));
    for (int i = 0; i < f1.number_of_components; i++)
        f1.components[i] = f.components[i];
    sort_components(f1);
    //clear screen
    //system("cls");
    if (skip == 1) {
        skip_lines();
    }
    //print separator line
    for (int i = 1; i < VIEW_COLS; i++) {
        printf("-");
    }
    printf("\n");
    int k = 0;
    //print view section
    for (int i = 1; i < VIEW_ROWS; i++) {
        int j = 1;
        if (k < f1.number_of_components) {
            while (f1.components[k].y == i && k < f1.number_of_components) {
                while (j < f1.components[k].x) {
                    printf(" ");
                    j++;
                }
                int component_width = 0;
                if (f1.components[k].type == 'l') {
                    while (component_width < strlen(f1.components[k].value) && component_width < \
            f1.components[k].width && j < VIEW_COLS) {
                        printf("%c", f1.components[k].value[component_width]);
                        component_width++;
                        j++;
                    }
                    while (component_width < f1.components[k].width && j < VIEW_COLS) {
                        printf("-");
                        component_width++;
                        j++;
                    }
                } else if (f1.components[k].type == 'b') {
                    while (component_width < strlen(f1.components[k].value) && component_width < \
            f1.components[k].width && j < VIEW_COLS) {
                        printf("%c", toupper(f1.components[k].value[component_width]));
                        component_width++;
                        j++;
                    }
                    while (component_width < f1.components[k].width && j < VIEW_COLS) {
                        printf("-");
                        component_width++;
                        j++;
                    }
                } else if (f1.components[k].type == 't') {
                    if (strlen(f1.components[k].value) == 0) {
                        while (component_width < f1.components[k].width && j < VIEW_COLS) {
                            printf("-");
                            component_width++;
                            j++;
                        }
                    } else if (strlen(f1.components[k].value) == 1) {
                        if (f1.components[k].value[0] == '\n') {
                            while (component_width < f1.components[k].width && j < VIEW_COLS) {
                                printf("-");
                                component_width++;
                                j++;
                            }
                        } else {
                            while (component_width < strlen(f1.components[k].value) && component_width < \
                f1.components[k].width && j < VIEW_COLS) {
                                printf("%c", f1.components[k].value[component_width]);
                                component_width++;
                                j++;
                            }
                            while (component_width < f1.components[k].width && j < VIEW_COLS) {
                                printf("-");
                                component_width++;
                                j++;
                            }
                        }
                    } else {
                        while (component_width < strlen(f1.components[k].value) && component_width < \
              f1.components[k].width && j < VIEW_COLS) {
                            printf("%c", f1.components[k].value[component_width]);
                            component_width++;
                            j++;
                        }
                        while (component_width < f1.components[k].width && j < VIEW_COLS) {
                            printf("-");
                            component_width++;
                            j++;
                        }
                    }
                }
                k++;
            }
        }
        printf("\n");
    }
    //print separator line
    for (int i = 1; i < VIEW_COLS; i++) {
        printf("-");
    }
    //print command section
    printf("\n");
    printf("Command> ");
}
//create a component according to input char (t = textbox & l = label & b = button )
Component create_component(char ch) {
    //input data
    Component c1;
    printf("x:");
    scanf("%d", & c1.x);
    printf("y:");
    scanf("%d", & c1.y);
    printf("width:");
    scanf("%d", & c1.width);
    getchar();
    switch (ch) {
        //create a zero_length value for textbox
        case 't':
            c1.type = ch;
            c1.value = (char * ) malloc(sizeof(char));
            c1.value[0] = '\0';
            break;
            //input value of button or label value for textbox
        case 'l':
        case 'b':
            c1.type = ch;
            printf("value: ");
            c1.value = (char * ) malloc(sizeof(char));
            char c = fgetc(stdin);
            int i = 1;
            while (c != '\n') {
                c1.value = (char * ) realloc(c1.value, i * sizeof(char));
                c1.value[i - 1] = c;
                i++;
                c = fgetc(stdin);
            }
            c1.value = (char * ) realloc(c1.value, i * sizeof(char));
            c1.value[i - 1] = '\0';
            break;
    }
    return c1;
}
//save created form
void save_form(Form f) {
    bool valid_name = false;
    char * fname;
    //input file name & check its validation . valid form name get saved in formsName.txt file.
    while (!valid_name) {
        f.name = (char * ) malloc(sizeof(char));
        char c = fgetc(stdin);
        int i = 1;
        while (c != '\n') {
            f.name = (char * ) realloc(f.name, i * sizeof(char));
            f.name[i - 1] = c;
            i++;
            c = fgetc(stdin);
        }
        f.name = (char * ) realloc(f.name, i * sizeof(char));
        f.name[i - 1] = '\0';
        FILE * p = fopen("formsName.txt", "r+");
        fname = (char * ) malloc(sizeof(char));
        i = 1;
        bool name_already_exists = false;
        if (p == NULL) {
            fclose(p);
            p = fopen("formsName.txt", "w+");
            fclose(p);
            p = fopen("formsName.txt", "r+");
        }
        if (p != NULL) {
            while (!feof(p) && !name_already_exists) {
                c = fgetc(p);
                fname = (char * ) realloc(fname, i * sizeof(char));
                fname[i - 1] = c;
                i++;
                if (c == '\n') {
                    fname = (char * ) realloc(fname, i * sizeof(char));
                    fname[i - 2] = '\0';
                    int a;
                    i = 1;
                    if (strcmpi(f.name, fname) == 0) {
                        name_already_exists = true;
                        free(f.name);
                        free(fname);
                        fclose(p);
                        printf("Form name already exists! Enter new form name:");
                    } else {
                        free(fname);
                        fname = (char * ) malloc(sizeof(char));
                    }
                    if (name_already_exists) {
                        break;
                    }
                }
                if (name_already_exists)
                    break;
            }
        }
        if (feof(p) && !name_already_exists) {
            valid_name = true;
            fclose(p);
            p = fopen("formsName.txt", "a+");
            fprintf(p, "%s\n", f.name);
            fclose(p);
        }
    }
    //form data get saved in forms.txt file .
    FILE * p = fopen("forms.txt", "a+");
    fprintf(p, "%s\n", f.name);
    fprintf(p, "%d\n", f.number_of_components);
    fprintf(p, "***\n");
    for (int i = 0; i < f.number_of_components; i++) {
        fprintf(p, "%c %d %d %d %d\n", f.components[i].type, f.components[i].x, \
      f.components[i].y, f.components[i].width, f.components[i].height);
        if (f.components[i].type == 't') {
            fprintf(p, "\n");
        } else {
            fprintf(p, "%s\n", f.components[i].value);
        }
        fprintf(p, "###\n");
    }
    fprintf(p, "$$$\n");
    fclose(p);
}
//load already saved form
Form load_form() {
    Form f;
    f.components = (Component * ) malloc(sizeof(Component));
    bool valid_name = false;
    char * name;
    char * fname;
    //input form name. validity is checked using formsName.txt file .
    while (!valid_name) {
        name = (char * ) malloc(sizeof(char));
        char c = fgetc(stdin);
        int i = 1;
        while (c != '\n') {
            name = (char * ) realloc(name, i * sizeof(char));
            name[i - 1] = c;
            i++;
            c = fgetc(stdin);
        }
        name = (char * ) realloc(name, i * sizeof(char));
        name[i - 1] = '\0';
        bool form_found = false;
        FILE * p = fopen("formsName.txt", "r+");
        fname = (char * ) malloc(sizeof(char));
        i = 1;
        if (p == NULL) {
            printf("No form to load! \n");
            return f;
        }
        if (p != NULL) {
            while (!feof(p)) {
                c = fgetc(p);
                fname = (char * ) realloc(fname, i * sizeof(char));
                fname[i - 1] = c;
                i++;
                if (c == '\n') {
                    fname = (char * ) realloc(fname, i * sizeof(char));
                    fname[i - 2] = '\0';
                    int a;
                    i = 1;
                    if (strcmpi(name, fname) == 0) {
                        form_found = true;
                        free(fname);
                        fclose(p);
                        break;
                    } else {
                        free(fname);
                        fname = (char * ) malloc(sizeof(char));
                    }
                }
            }
        }
        if (!form_found) {
            fclose(p);
            printf("No form with this name! Enter new form name: ");
        } else if (form_found) {
            valid_name = true;
            fclose(p);
        }
    }
    //read form data from forms.txt file.
    char c;
    int i = 1;
    f.name = (char * ) malloc(strlen(name) * sizeof(char));
    strcpy(f.name, name);
    char * line = (char * ) malloc(sizeof(char));
    FILE * p = fopen("forms.txt", "r+");
    while (!feof(p)) {
        c = fgetc(p);
        line = (char * ) realloc(line, i * sizeof(char));
        line[i - 1] = c;
        i++;
        if (c == '\n') {
            line = (char * ) realloc(line, i * sizeof(char));
            line[i - 2] = '\0';
            i = 1;
            if (strcmpi(name, line) == 0) {
                fscanf(p, "%d\n", & f.number_of_components);
                free(line);
                line = (char * ) malloc(sizeof(char));
                c = fgetc(p);
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 1] = c;
                i++;
                while (c != '\n') {
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                }
                if (c == '\n') {
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 2] = '\0';
                }
                free(line);
                f.components = (Component * ) malloc(f.number_of_components * sizeof(Component));
                for (int j = 0; j < f.number_of_components; j++) {
                    fscanf(p, "%c %d %d %d %d\n", & f.components[j].type, & f.components[j].x, &
                            f.components[j].y, & f.components[j].width, & f.components[j].height);
                    line = (char * ) malloc(sizeof(char));
                    i = 1;
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                    while (c != '\n') {
                        c = fgetc(p);
                        line = (char * ) realloc(line, i * sizeof(char));
                        line[i - 1] = c;
                        i++;
                    }
                    if (c == '\n') {
                        line = (char * ) realloc(line, i * sizeof(char));
                        line[i - 2] = '\0';
                    }
                    if (strcmp(line, "###") == 0) {
                        line[0] = '\0';
                    }
                    f.components[j].value = (char * ) malloc(strlen(line) * sizeof(char));
                    strcpy(f.components[j].value, line);
                    free(line);
                    line = (char * ) malloc(sizeof(char));
                    i = 1;
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                    while (c != '\n') {
                        c = fgetc(p);
                        line = (char * ) realloc(line, i * sizeof(char));
                        line[i - 1] = c;
                        i++;
                    }
                    if (c == '\n') {
                        line = (char * ) realloc(line, i * sizeof(char));
                        line[i - 2] = '\0';
                    }
                }
                free(line);
                fclose(p);
                return f;
            } else {
                free(line);
                line = (char * ) malloc(sizeof(char));
            }
        }
    }
    return f;
}
//update edited form in forms.txt file.
void save_edited_form(Form f) {
    FILE * p = fopen("forms.txt", "r+");
    FILE * t = fopen("temp.txt", "a+");
    char * line = (char * ) malloc(sizeof(char));
    char c;
    int i = 1;
    bool form_found = false;
    //read all old forms
    while (!feof(p)) {
        c = fgetc(p);
        line = (char * ) realloc(line, i * sizeof(char));
        line[i - 1] = c;
        i++;
        if (c == '\n') {
            line = (char * ) realloc(line, i * sizeof(char));
            line[i - 2] = '\0';
            i = 1;
            //find recently edited form
            if (strcmpi(f.name, line) == 0) {
                free(line);
                line = (char * ) malloc(sizeof(char));
                //read old data of recently edited form and skip it
                while (!feof(p)) {
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                    if (c == '\n') {
                        line = (char * ) realloc(line, i * sizeof(char));
                        line[i - 2] = '\0';
                        i = 1;
                        if (strcmpi("$$$", line) == 0) {
                            free(line);
                            line = (char * ) malloc(sizeof(char));
                            break;
                        }
                    }
                }
                //write new data of recently edited form.
                fprintf(t, "%s\n", f.name);
                fprintf(t, "%d\n", f.number_of_components);
                fprintf(t, "***\n");
                for (int i = 0; i < f.number_of_components; i++) {
                    fprintf(t, "%c %d %d %d %d\n", f.components[i].type, f.components[i].x, \
            f.components[i].y, f.components[i].width, f.components[i].height);
                    if (f.components[i].type == 't') {
                        fprintf(t, "\n");
                    } else {
                        fprintf(t, "%s\n", f.components[i].value);
                    }
                    fprintf(t, "###\n");
                }
                fprintf(t, "$$$\n");
            }
                //write data of other forms.
            else {
                fprintf(t, "%s\n", line);
                free(line);
                line = (char * ) malloc(sizeof(char));
            }
        }
    }
    fclose(p);
    fclose(t);
    remove("forms.txt");
    rename("temp.txt", "forms.txt");
}
//edit loaded form
void edit_form(Form f) {
    char * command = (char * ) malloc(7 * sizeof(char));
    //loop until cancel is clicked.
    while (1) {
        printf("> add | edit | remove | cancel | save:");
        gets(command);
        if (strcmpi(command, "edit") == 0 || strcmpi(command, "remove") == 0) {
            int i = 0;
            //loop on forms components .
            while (1) {
                printf("Component properties: \n");
                if (f.components[i].type == 'l') {
                    printf("type:label ");
                } else if (f.components[i].type == 'b') {
                    printf("type:button ");
                } else if (f.components[i].type == 't') {
                    printf("type:textbox ");
                }
                printf("x:%d y:%d width:%d height:%d\n", f.components[i].x, f.components[i].y, \
          f.components[i].width, f.components[i].height);
                if (f.components[i].type != 't') {
                    printf("value:%s\n", f.components[i].value);
                }
                printf("command> edit | next | previous | remove | cancel | save :");
                gets(command);
                //edit current component
                if (strcmpi(command, "edit") == 0) {
                    print_view(f, 1);
                    printf("\nx:");
                    scanf("%d", & f.components[i].x);
                    printf("y:");
                    scanf("%d", & f.components[i].y);
                    printf("width:");
                    scanf("%d", & f.components[i].width);
                    if (f.components[i].type != 't') {
                        getchar();
                        printf("value:");
                        free(f.components[i].value);
                        f.components[i].value = (char * ) malloc(sizeof(char));
                        char c = fgetc(stdin);
                        int j = 1;
                        while (c != '\n') {
                            f.components[i].value = (char * ) realloc(f.components[i].value, j * \
                sizeof(char));
                            f.components[i].value[j - 1] = c;
                            j++;
                            c = fgetc(stdin);
                        }
                        f.components[i].value = (char * ) realloc(f.components[i].value, j * \
              sizeof(char));
                        f.components[i].value[j - 1] = '\0';
                    }
                    if (i + 1 == f.number_of_components) {
                        if (f.components[i].type == 't')
                            getchar();
                        printf("command> cancel | save :");
                        gets(command);
                        if (strcmpi(command, "cancel") == 0) {
                            break;
                        } else if (strcmpi(command, "save") == 0) {
                            save_edited_form(f);
                            print_view(f, 1);
                            printf("Edit saved!\n");
                            break;
                        }
                    }
                }
                    //remove current component
                else if (strcmpi(command, "remove") == 0) {
                    for (int j = i; j < f.number_of_components - 1; j++) {
                        f.components[j] = f.components[j + 1];
                    }
                    f.number_of_components--;
                }
                    //go to next component
                else if (strcmpi(command, "next") == 0) {
                    print_view(f, 1);
                    i = (i + 1) % f.number_of_components;
                }
                    //go to previous component
                else if (strcmpi(command, "previous") == 0) {
                    print_view(f, 1);
                    i--;
                    if (i < 0)
                        i = f.number_of_components - 1;
                }
                    //go to previous menu
                else if (strcmpi(command, "cancel") == 0) {
                    break;
                }
                    //save edited form using save_edited_form() function.
                else if (strcmpi(command, "save") == 0) {
                    save_edited_form(f);
                    print_view(f, 1);
                    printf("Edit saved!\n");
                    break;
                }
                print_view(f, 1);
            }
        }
            //add a new component to form using create_form() function.
        else if (strcmpi(command, "add") == 0) {
            printf("> component type (label | textbox | button):");
            gets(command);
            f.number_of_components++;
            f.components = (Component * ) realloc(f.components, f.number_of_components * \
        sizeof(Component));
            Component c;
            if (strcmpi(command, "textbox") == 0) {
                c = create_component('t');
                f.components[f.number_of_components - 1] = c;
                print_view(f, 1);
            } else if (strcmpi(command, "label") == 0) {
                c = create_component('l');
                f.components[f.number_of_components - 1] = c;
                print_view(f, 1);
            } else if (strcmpi(command, "button") == 0) {
                c = create_component('b');
                f.components[f.number_of_components - 1] = c;
                print_view(f, 1);
            } else {
                printf("Invalid input\n");
            }
            print_view(f, 1);
        }
            //save edited form using save_edited_form() function
        else if (strcmpi(command, "save") == 0) {
            save_edited_form(f);
            print_view(f, 1);
            break;
        }
            //return to run or edit menu
        else if (strcmpi(command, "cancel") == 0) {
            break;
        }
    }
}
//save data of ran form which was filled in {form.name}_data.txt file .
void save_form_data(Form f) {
    //build file name
    char * name = (char * ) malloc((9 + strlen(f.name)) * sizeof(char));
    strcpy(name, f.name);
    strcat(name, "_data.txt");
    FILE * p = fopen(name, "a+");
    //write form data in {form.name}_data.txt file .
    fprintf(p, "%s\n", f.name);
    fprintf(p, "%d\n", f.number_of_components);
    fprintf(p, "***\n");
    for (int i = 0; i < f.number_of_components; i++) {
        fprintf(p, "%c %d %d %d %d\n", f.components[i].type, f.components[i].x, \
      f.components[i].y, f.components[i].width, f.components[i].height);
        fprintf(p, "%s\n", f.components[i].value);
        fprintf(p, "###\n");
    }
    fprintf(p, "$$$\n");
    fclose(p);
}

void find_forms(Form f) {
    char * command = (char * ) malloc(10 * sizeof(char));
    //build file name.
    char * name = (char * ) malloc((10 + strlen(f.name)) * sizeof(char));
    strcpy(name, f.name);
    strcat(name, "_data.txt");
    FILE * p = fopen(name, "r+");
    char * line = (char * ) malloc(sizeof(char));
    char c;
    int i = 1;
    //array of forms to store all matched forms.
    Form * forms = (Form * ) malloc(sizeof(Form));
    int number_of_forms = 0;
    //read related file to find similar forms.
    while (!feof(p)) {
        //form to store read form from related file.
        Form f1;
        c = fgetc(p);
        i = 1;
        line = (char * ) realloc(line, i * sizeof(char));
        line[i - 1] = c;
        i++;
        bool form_read = false;
        if (c == '\n') {
            line = (char * ) realloc(line, i * sizeof(char));
            line[i - 2] = '\0';
            i = 1;
            fscanf(p, "%d\n", & f1.number_of_components);
            free(line);
            line = (char * ) malloc(sizeof(char));
            c = fgetc(p);
            line = (char * ) realloc(line, i * sizeof(char));
            line[i - 1] = c;
            i++;
            while (c != '\n') {
                c = fgetc(p);
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 1] = c;
                i++;
            }
            if (c == '\n') {
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 2] = '\0';
            }
            free(line);
            f1.components = (Component * ) malloc(f1.number_of_components * sizeof(Component));
            for (int j = 0; j < f.number_of_components; j++) {
                fscanf(p, "%c %d %d %d %d\n", & f1.components[j].type, & f1.components[j].x, &
                        f1.components[j].y, & f1.components[j].width, & f1.components[j].height);
                line = (char * ) malloc(sizeof(char));
                i = 1;
                c = fgetc(p);
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 1] = c;
                i++;
                while (c != '\n') {
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                }
                if (c == '\n') {
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 2] = '\0';
                }
                if (strcmp(line, "###") == 0) {
                    line[0] = '\0';
                }
                f1.components[j].value = (char * ) malloc(strlen(line) * sizeof(char));
                strcpy(f1.components[j].value, line);
                free(line);
                line = (char * ) malloc(sizeof(char));
                i = 1;
                c = fgetc(p);
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 1] = c;
                i++;
                while (c != '\n') {
                    c = fgetc(p);
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 1] = c;
                    i++;
                }
                if (c == '\n') {
                    line = (char * ) realloc(line, i * sizeof(char));
                    line[i - 2] = '\0';
                }
                free(line);
            }
            i = 1;
            c = fgetc(p);
            line = (char * ) malloc(i * sizeof(char));
            line[i - 1] = c;
            i++;
            while (c != '\n' && !feof(p)) {
                c = fgetc(p);
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 1] = c;
                i++;
            }
            if (c == '\n' || feof(p)) {
                line = (char * ) realloc(line, i * sizeof(char));
                line[i - 2] = '\0';
            }
            free(line);
            line = (char * ) malloc(sizeof(char));
            form_read = true;
        }
        if (form_read) {
            //check if form read from the file matches base (input) form.
            bool forms_match = true;
            for (int k = 0; k < f1.number_of_components; k++) {
                if (f1.components[k].type == 't') {
                    if (strcmp(f.components[k].value, "\n") != 0) {
                        if (strcmp(f1.components[k].value, f.components[k].value) != 0) {
                            forms_match = false;
                            break;
                        }
                    }
                }
            }
            //add data of form read from file to array of matched forms if it matches base form .
            if (forms_match) {
                forms[number_of_forms].number_of_components = f1.number_of_components;
                forms[number_of_forms].components = (Component * ) malloc(f1.number_of_components * \
          sizeof(Component));
                for (int k = 0; k < f1.number_of_components; k++) {
                    forms[number_of_forms].components[k].x = f1.components[k].x;
                    forms[number_of_forms].components[k].y = f1.components[k].y;
                    forms[number_of_forms].components[k].width = f1.components[k].width;
                    forms[number_of_forms].components[k].height = f1.components[k].height;
                    forms[number_of_forms].components[k].type = f1.components[k].type;
                    forms[number_of_forms].components[k].value = (char * ) malloc(strlen(f1.components[k].value) * \
            sizeof(char));
                    strcpy(forms[number_of_forms].components[k].value, f1.components[k].value);
                }
                number_of_forms++;
                forms = (Form * ) realloc(forms, (number_of_forms + 1) * sizeof(Form));
            }
        }
    }
    fclose(p);
    int k = 0;
    //return to previous menu if no forms matched .
    if (number_of_forms == 0) {
        printf("No forms found!\n");
        getch();
        return;
    }
    //loop through matched forms .
    while (1) {
        print_view(forms[k], 1);
        printf("form %d of %d \n> edit | remove | next | previous | cancel :", k + 1, number_of_forms);
        gets(command);
        //edit current form data (textboxes).
        if (strcmpi(command, "edit") == 0) {
            int i = 0;
            bool form_with_textbox = true;
            //check if current form contains any textbox.
            while (forms[k].components[i].type != 't') {
                i = (i + 1);
                if (i == forms[k].number_of_components) {
                    printf("No textbox in form!\n");
                    getch();
                    form_with_textbox = false;
                    break;
                }
            }
            //loop through current form components (textboxes).
            while (form_with_textbox) {
                while (forms[k].components[i].type != 't') {
                    i = (i + 1) % forms[k].number_of_components;
                }
                print_view(forms[k], 1);
                printf("Component properties: \n");
                /*if (f.components[i].type == 'b'){
                    printf("type:button ");
                }*/
                if (forms[k].components[i].type == 't') {
                    printf("type:textbox ");
                }
                printf("x:%d y:%d width:%d height:%d\n", forms[k].components[i].x, forms[k].components[i].y, \
          forms[k].components[i].width, forms[k].components[i].height);
                printf("Command> edit | next | previous | ok | exit :");
                gets(command);
                //edit current component (textbox) of current form .
                if (strcmpi(command, "edit") == 0) {
                    p = fopen(name, "a+");
                    FILE * t = fopen("temp.txt", "w+");
                    fseek(p, 0, SEEK_SET);
                    int b = 1;
                    //make a copy of current form
                    Form copy_form;
                    copy_form.number_of_components = forms[k].number_of_components;
                    copy_form.components = (Component * ) malloc(copy_form.number_of_components * sizeof(Component));
                    for (int y = 0; y < copy_form.number_of_components; y++) {
                        copy_form.components[y].x = forms[k].components[y].x;
                        copy_form.components[y].y = forms[k].components[y].y;
                        copy_form.components[y].width = forms[k].components[y].width;
                        copy_form.components[y].height = forms[k].components[y].height;
                        copy_form.components[y].type = forms[k].components[y].type;
                        copy_form.components[y].value = (char * ) malloc(sizeof(char) * strlen(forms[k].components[y].value));
                        strcpy(copy_form.components[y].value, forms[k].components[y].value);
                    }
                    printf(">value:");
                    free(forms[k].components[i].value);
                    forms[k].components[i].value = (char * ) malloc(sizeof(char));
                    char c = fgetc(stdin);
                    int j = 1;
                    while (c != '\n') {
                        forms[k].components[i].value = (char * ) realloc(forms[k].components[i].value, j * sizeof(char));
                        forms[k].components[i].value[j - 1] = c;
                        j++;
                        c = fgetc(stdin);
                    }
                    forms[k].components[i].value = (char * ) realloc(forms[k].components[i].value, j * sizeof(char));
                    forms[k].components[i].value[j - 1] = '\0';
                    bool form_not_written = true;
                    int form_index = -1;
                    //read all forms from related file.
                    while (!feof(p)) {
                        Form f1;
                        c = fgetc(p);
                        b = 1;
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 1] = c;
                        b++;
                        bool form_read = false;
                        if (c == '\n') {
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 2] = '\0';
                            b = 1;
                            fscanf(p, "%d\n", & f1.number_of_components);
                            free(line);
                            line = (char * ) malloc(sizeof(char));
                            c = fgetc(p);
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 1] = c;
                            b++;
                            while (c != '\n') {
                                c = fgetc(p);
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 1] = c;
                                b++;
                            }
                            if (c == '\n') {
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 2] = '\0';
                            }
                            free(line);
                            f1.components = (Component * ) malloc(f1.number_of_components * sizeof(Component));
                            for (int j = 0; j < f.number_of_components; j++) {
                                fscanf(p, "%c %d %d %d %d\n", & f1.components[j].type, & f1.components[j].x, &
                                        f1.components[j].y, & f1.components[j].width, & f1.components[j].height);
                                line = (char * ) malloc(sizeof(char));
                                b = 1;
                                c = fgetc(p);
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 1] = c;
                                b++;
                                while (c != '\n') {
                                    c = fgetc(p);
                                    line = (char * ) realloc(line, b * sizeof(char));
                                    line[b - 1] = c;
                                    b++;
                                }
                                if (c == '\n') {
                                    line = (char * ) realloc(line, b * sizeof(char));
                                    line[b - 2] = '\0';
                                }
                                if (strcmp(line, "###") == 0) {
                                    line[0] = '\0';
                                }
                                f1.components[j].value = (char * ) malloc(strlen(line) * sizeof(char));
                                strcpy(f1.components[j].value, line);
                                free(line);
                                line = (char * ) malloc(sizeof(char));
                                b = 1;
                                c = fgetc(p);
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 1] = c;
                                b++;
                                while (c != '\n') {
                                    c = fgetc(p);
                                    line = (char * ) realloc(line, b * sizeof(char));
                                    line[b - 1] = c;
                                    b++;
                                }
                                if (c == '\n') {
                                    line = (char * ) realloc(line, b * sizeof(char));
                                    line[b - 2] = '\0';
                                }
                                free(line);
                            }
                            b = 1;
                            c = fgetc(p);
                            line = (char * ) malloc(b * sizeof(char));
                            line[b - 1] = c;
                            b++;
                            while (c != '\n' && !feof(p)) {
                                c = fgetc(p);
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 1] = c;
                                b++;
                            }
                            if (c == '\n' || feof(p)) {
                                line = (char * ) realloc(line, b * sizeof(char));
                                line[b - 2] = '\0';
                            }
                            free(line);
                            line = (char * ) malloc(sizeof(char));
                            form_read = true;
                        }
                        if (form_read) {
                            bool forms_match = true;
                            for (int y = 0; y < f1.number_of_components; y++) {
                                if (f1.components[y].type == 't') {
                                    if (copy_form.components[y].value != "\n") {
                                        if (strcmp(f1.components[y].value, copy_form.components[y].value) != 0) {
                                            forms_match = false;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (forms_match) {
                                form_index = (form_index + 1) % number_of_forms;
                            }
                            if (forms_match && form_not_written && k == form_index) {
                                form_not_written = false;
                                fprintf(t, "%s\n", f.name);
                                fprintf(t, "%d\n", forms[k].number_of_components);
                                fprintf(t, "***\n");
                                for (int i = 0; i < forms[k].number_of_components; i++) {
                                    fprintf(t, "%c %d %d %d %d\n", forms[k].components[i].type, forms[k].components[i].x, \
                    forms[k].components[i].y, forms[k].components[i].width, forms[k].components[i].height);
                                    if (forms[k].components[i].type == 't') {
                                        if (forms[k].components[i].value[0] == '\n')
                                            fprintf(t, "\n");
                                        else
                                            fprintf(t, "%s\n", forms[k].components[i].value);
                                    } else {
                                        fprintf(t, "%s\n", forms[k].components[i].value);
                                    }
                                    fprintf(t, "###\n");
                                }
                                fprintf(t, "$$$\n");
                            } else {
                                fprintf(t, "%s\n", f.name);
                                fprintf(t, "%d\n", f1.number_of_components);
                                fprintf(t, "***\n");
                                for (int i = 0; i < forms[k].number_of_components; i++) {
                                    fprintf(t, "%c %d %d %d %d\n", f1.components[i].type, f1.components[i].x, \
                    f1.components[i].y, f1.components[i].width, f1.components[i].height);
                                    if (f1.components[i].type == 't') {
                                        if (f1.components[i].value[0] == '\n')
                                            fprintf(t, "\n");
                                        else
                                            fprintf(t, "%s\n", f1.components[i].value);
                                    } else {
                                        fprintf(t, "%s\n", f1.components[i].value);
                                    }
                                    fprintf(t, "###\n");
                                }
                                fprintf(t, "$$$\n");
                            }
                        }
                    }
                    fclose(p);
                    fclose(t);
                }
                    //go to next component of current form
                else if (strcmpi(command, "next") == 0) {
                    i = (i + 1) % forms[k].number_of_components;
                }
                    //go to previous component of current form
                else if (strcmpi(command, "previous") == 0) {
                    i--;
                    if (i < 0) {
                        i = forms[k].number_of_components - 1;
                    }
                }
                    //save edited form in related file
                else if (strcmpi(command, "ok") == 0) {
                    remove(name);
                    rename("temp.txt", name);
                    if (k >= number_of_forms - 1)
                        k--;
                    for (int a = k; a < number_of_forms - 1; a++) {
                        forms[a] = forms[a + 1];
                    }
                    number_of_forms--;
                    break;
                }
                    //return to find menu
                else if (strcmpi(command, "exit") == 0) {
                    FILE * file;
                    if ((file = fopen("temp.txt", "r"))) {
                        fclose(file);
                        remove("temp.txt");
                    }
                    break;
                } else {
                    printf("Invalid input !\n");
                }
            }
        }
            //remove current matched form
        else if (strcmpi(command, "remove") == 0) {
            p = fopen(name, "a+");
            FILE * t = fopen("temp.txt", "w+");
            fseek(p, 0, SEEK_SET);
            int b = 1;
            bool form_not_written = true;
            int form_index = -1;
            while (!feof(p)) {
                Form f1;
                c = fgetc(p);
                b = 1;
                line = (char * ) realloc(line, b * sizeof(char));
                line[b - 1] = c;
                b++;
                bool form_read = false;
                if (c == '\n') {
                    line = (char * ) realloc(line, b * sizeof(char));
                    line[b - 2] = '\0';
                    printf("%s\n", line);
                    b = 1;
                    fscanf(p, "%d\n", & f1.number_of_components);
                    free(line);
                    line = (char * ) malloc(sizeof(char));
                    c = fgetc(p);
                    line = (char * ) realloc(line, b * sizeof(char));
                    line[b - 1] = c;
                    b++;
                    while (c != '\n') {
                        c = fgetc(p);
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 1] = c;
                        b++;
                    }
                    if (c == '\n') {
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 2] = '\0';
                    }
                    free(line);
                    f1.components = (Component * ) malloc(f1.number_of_components * sizeof(Component));
                    for (int j = 0; j < f.number_of_components; j++) {
                        fscanf(p, "%c %d %d %d %d\n", & f1.components[j].type, & f1.components[j].x, &
                                f1.components[j].y, & f1.components[j].width, & f1.components[j].height);
                        line = (char * ) malloc(sizeof(char));
                        b = 1;
                        c = fgetc(p);
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 1] = c;
                        b++;
                        while (c != '\n') {
                            c = fgetc(p);
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 1] = c;
                            b++;
                        }
                        if (c == '\n') {
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 2] = '\0';
                        }
                        if (strcmp(line, "###") == 0) {
                            line[0] = '\0';
                        }
                        f1.components[j].value = (char * ) malloc(strlen(line) * sizeof(char));
                        strcpy(f1.components[j].value, line);
                        free(line);
                        line = (char * ) malloc(sizeof(char));
                        b = 1;
                        c = fgetc(p);
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 1] = c;
                        b++;
                        while (c != '\n') {
                            c = fgetc(p);
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 1] = c;
                            b++;
                        }
                        if (c == '\n') {
                            line = (char * ) realloc(line, b * sizeof(char));
                            line[b - 2] = '\0';
                        }
                        free(line);
                    }
                    b = 1;
                    c = fgetc(p);
                    line = (char * ) malloc(b * sizeof(char));
                    line[b - 1] = c;
                    b++;
                    while (c != '\n' && !feof(p)) {
                        c = fgetc(p);
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 1] = c;
                        b++;
                    }
                    if (c == '\n' || feof(p)) {
                        line = (char * ) realloc(line, b * sizeof(char));
                        line[b - 2] = '\0';
                    }
                    free(line);
                    line = (char * ) malloc(sizeof(char));
                    form_read = true;
                }
                if (form_read) {
                    bool forms_match = true;
                    for (int y = 0; y < f1.number_of_components; y++) {
                        if (f1.components[y].type == 't') {
                            if (f1.components[y].value != "\n") {
                                if (strcmp(f1.components[y].value, forms[k].components[y].value) != 0) {
                                    forms_match = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (forms_match) {
                        form_index = (form_index + 1) % number_of_forms;
                    }
                    if (forms_match && form_not_written && k == form_index) {
                        form_not_written = false;
                    } else {
                        fprintf(t, "%s\n", f.name);
                        fprintf(t, "%d\n", f1.number_of_components);
                        fprintf(t, "***\n");
                        for (int i = 0; i < f1.number_of_components; i++) {
                            fprintf(t, "%c %d %d %d %d\n", f1.components[i].type, f1.components[i].x, \
                f1.components[i].y, f1.components[i].width, f1.components[i].height);
                            if (f1.components[i].type == 't') {
                                if (f1.components[i].value[0] == '\n')
                                    fprintf(t, "\n");
                                else
                                    fprintf(t, "%s\n", f1.components[i].value);
                            } else {
                                fprintf(t, "%s\n", f1.components[i].value);
                            }
                            fprintf(t, "###\n");
                        }
                        fprintf(t, "$$$\n");
                    }
                }
            }
            fclose(p);
            fclose(t);
            remove(name);
            rename("temp.txt", name);
            if (k >= number_of_forms - 1)
                k--;
            for (int a = k; a < number_of_forms - 1; a++) {
                forms[a] = forms[a + 1];
            }
            number_of_forms--;
        }
            //go to next matched form
        else if (strcmpi(command, "next") == 0) {
            k = (k + 1) % number_of_forms;
        }
            //go to previous matched form
        else if (strcmpi(command, "previous") == 0) {
            k--;
            if (k < 0) {
                k = number_of_forms - 1;
            }
        }
            //go to run or edit menu
        else if (strcmpi(command, "cancel") == 0) {
            break;
        }
    }
}
//run loaded form
void run_form(Form f) {
    int i = 0;
    bool form_with_textbox = true;
    //printf("Command> add | find | edit | remove | ok | next | previous | exit :");
    char * command = (char * ) malloc(9 * sizeof(char));
    //check if form contains any textbox.
    while (f.components[i].type != 't') {
        i = (i + 1);
        if (i == f.number_of_components) {
            printf("No textbox in form!\n");
            getch();
            form_with_textbox = false;
            break;
        }
    }
    i = 0;
    //run current form if it contains textbox.
    while (form_with_textbox) {
        //loop until a textbox is found.
        while (f.components[i].type != 't') {
            i = (i + 1) % f.number_of_components;
        }
        print_view(f, 1);
        printf("Component properties: \n");
        /*if (f.components[i].type == 'b'){
            printf("type:button ");
        }*/
        if (f.components[i].type == 't') {
            printf("type:textbox ");
        }
        printf("x:%d y:%d width:%d height:%d\n", f.components[i].x, f.components[i].y, \
      f.components[i].width, f.components[i].height);
        printf("Command> add | find | fill | next | previous | exit :");
        gets(command);
        //save filled form using save_form_data() function.
        if (strcmpi(command, "add") == 0) {
            save_form_data(f);
            printf("Form added!\n");
        }
            //search for forms similar to filled form using find_forms() function.
        else if (strcmpi(command, "find") == 0) {
            find_forms(f);
        }
            //fill data of current component (textbox) of the form.
        else if (strcmpi(command, "fill") == 0) {
            printf(">value:");
            free(f.components[i].value);
            f.components[i].value = (char * ) malloc(sizeof(char));
            char c = fgetc(stdin);
            int j = 1;
            while (c != '\n') {
                f.components[i].value = (char * ) realloc(f.components[i].value, j * sizeof(char));
                f.components[i].value[j - 1] = c;
                j++;
                c = fgetc(stdin);
            }
            f.components[i].value = (char * ) realloc(f.components[i].value, j * sizeof(char));
            f.components[i].value[j - 1] = '\0';
        }
            //go to next component (textbox) of the form
        else if (strcmpi(command, "next") == 0) {
            i = (i + 1) % f.number_of_components;
        }
            //go to previous component (textbox) of the form
        else if (strcmpi(command, "previous") == 0) {
            i--;
            if (i < 0) {
                i = f.number_of_components - 1;
            }
        }
            //return to run | edit menu.
        else if (strcmpi(command, "exit") == 0) {
            return;
        }
    }
}

int main() {
    char * command = (char * ) malloc(7 * sizeof(char));
    //loop until exit is clicked.
    while (1) {
        Form f;
        print_view(f, 0);
        printf("create | load | exit:");
        //input command
        gets(command);
        if (strcmpi(command, "exit") != 0) {
            print_view(f, 1);
        }
        if (strcmpi(command, "create") == 0) {
            f.components = (Component * ) malloc(sizeof(Component));
            //loop until cancel is clicked & create components.
            while (1) {
                printf("create {label | textbox | button} | save | cancel :");
                free(command);
                command = (char * ) malloc(sizeof(char));
                char c = fgetc(stdin);
                int i = 1;
                while (c != '\n') {
                    command = (char * ) realloc(command, i * sizeof(char));
                    command[i - 1] = c;
                    i++;
                    c = fgetc(stdin);
                }
                command = (char * ) realloc(command, i * sizeof(char));
                command[i - 1] = '\0';
                char * subcommand1 = (char * ) malloc(sizeof(char));
                i = 1;
                while (command[i - 1] != ' ' && command[i - 1] != '\n' && command[i - 1] != '\0') {
                    subcommand1 = (char * ) realloc(subcommand1, i * sizeof(char));
                    subcommand1[i - 1] = command[i - 1];
                    i++;
                }
                subcommand1 = (char * ) realloc(subcommand1, i * sizeof(char));
                subcommand1[i - 1] = '\0';
                if (strcmpi(subcommand1, "create") == 0) {
                    free(subcommand1);
                    subcommand1 = (char * ) malloc(sizeof(char));
                    int j = 1;
                    i++;
                    while (command[i - 1] != ' ' && command[i - 1] != '\n' && command[i - 1] != '\0') {
                        subcommand1 = (char * ) realloc(subcommand1, j * sizeof(char));
                        subcommand1[j - 1] = command[i - 1];
                        i++;
                        j++;
                    }
                    subcommand1 = (char * ) realloc(subcommand1, j * sizeof(char));
                    subcommand1[j - 1] = '\0';
                    Component c;
                    //create a component by inputting data.
                    if (strcmpi(subcommand1, "textbox") == 0) {
                        free(subcommand1);
                        c = create_component('t');
                        f.components[f.number_of_components] = c;
                        f.number_of_components++;
                        f.components = (Component * ) realloc(f.components, (f.number_of_components + 1) *
                                                                            sizeof(Component));
                        print_view(f, 1);
                    } else if (strcmpi(subcommand1, "label") == 0) {
                        free(subcommand1);
                        c = create_component('l');
                        f.components[f.number_of_components] = c;
                        f.number_of_components++;
                        f.components = (Component * ) realloc(f.components, (f.number_of_components + 1) *
                                                                            sizeof(Component));
                        print_view(f, 1);
                    } else if (strcmpi(subcommand1, "button") == 0) {
                        free(subcommand1);
                        c = create_component('b');
                        f.components[f.number_of_components] = c;
                        f.number_of_components++;
                        f.components = (Component * ) realloc(f.components, (f.number_of_components + 1) *
                                                                            sizeof(Component));
                        print_view(f, 1);
                    } else {
                        free(subcommand1);
                        printf("Invalid input\n");
                    }
                }
                    //call save_form() function to save a form if save is clicked .
                else if (strcmpi(subcommand1, "save") == 0) {
                    free(subcommand1);
                    printf("Enter form name: ");
                    save_form(f);
                    break;
                }
                    //return to create or load menu without saving the created form.
                else if (strcmpi(subcommand1, "cancel") == 0) {
                    free(subcommand1);
                    break;
                }
            }
        }
            //load a form using inputted form name by calling load_form() function if load is clicked
        else if (strcmpi(command, "load") == 0) {
            printf("Enter form name: ");
            f = load_form();
            free(command);
            //loop until cancel is clicked and run or edit loaded form .
            while (1) {
                print_view(f, 1);
                printf("run | edit | cancel:");
                command = (char * ) malloc(sizeof(char));
                char c = fgetc(stdin);
                int i = 1;
                while (c != '\n') {
                    command = (char * ) realloc(command, i * sizeof(char));
                    command[i - 1] = c;
                    i++;
                    c = fgetc(stdin);
                }
                command = (char * ) realloc(command, i * sizeof(char));
                command[i - 1] = '\0';
                //run loaded form by calling run_form() function if run is clicked .
                if (strcmpi(command, "run") == 0) {
                    free(command);
                    run_form(f);
                }
                    //edit loaded form by calling edit_form() function if edit is clicked .
                else if (strcmpi(command, "edit") == 0) {
                    free(command);
                    edit_form(f);
                }
                    //return to create or load menu .
                else if (strcmpi(command, "cancel") == 0) {
                    free(command);
                    command = (char * ) malloc(7 * sizeof(char));
                    break;
                } else {
                    free(command);
                    printf("Invalid input!\n");
                }
            }
        }
            //exit program if exit is clicked.
        else if (strcmpi(command, "exit") == 0) {
            free(command);
            break;
        } else {
            free(command);
            printf("Invalid input!\n");
        }
    }
    return 0;
}