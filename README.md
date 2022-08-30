# text editor
It is a student project.
A simple command line text editor with some restriction on using C++ features
### compile
```shell
$ g++ main.cpp text_editor.cpp
```
- open the app

```shell
$ ./a.out
```
- get help
```
>> help
```
output will be:
```
        open    open the given "file" and store it into TEXT
        save    save TEXT into given "file"
        show    show TEXT
      insert    insert user words in user pos
      select    select from user pos as many as user len
        move    move a string in TEXT to user pos
        copy    store string from user pos as many as user len in CLIPBOARD
       paste    paste any thing from CLIPBOARD in user pos
       erase    erase from user pos as many as user len
       clear    truncate TEXT
        find    find user string
     replace    replace a string with user string
     addline    add new line ad given "pos"
    moveline    move a line to given "pos"
    copyline    copy given "line" a paste into given "pos"
   clearline    truncate given "line"
     rmlines    remove a bunch of "lines" from given "pos"
      rmline    remove given "line"
        exit    close the editor
```
