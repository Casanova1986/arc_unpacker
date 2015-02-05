#include <cassert>
#include <cstring>
#include "io.h"
#include "logger.h"
#include "string_ex.h"
#include "virtual_file.h"

typedef struct
{
    char *name;
} Internals;

VirtualFile *virtual_file_create()
{
    VirtualFile *file = new VirtualFile;
    assert(file != nullptr);

    file->io = io_create_empty();
    assert(file->io != nullptr);

    Internals *internals = new Internals;
    assert(internals != nullptr);
    internals->name = nullptr;
    file->internals = internals;

    return file;
}

void virtual_file_destroy(VirtualFile *file)
{
    assert(file != nullptr);
    io_destroy(file->io);
    delete []((Internals*)file->internals)->name;
    delete (Internals*)file->internals;
    delete file;
}

void virtual_file_change_extension(VirtualFile *file, const char *new_ext)
{
    char *name = ((Internals*)file->internals)->name;
    assert(file != nullptr);
    if (name == nullptr)
        return;

    char *ptr = strrchr(name, '.');
    if (ptr != nullptr)
        *ptr = '\0';

    while (new_ext[0] == '.')
        new_ext ++;

    size_t base_length = strlen(name);
    char *new_name = new char[base_length + 1 + strlen(new_ext) + 1];
    assert(new_name != nullptr);
    strcpy(new_name, name);
    strcpy(new_name + base_length, ".");
    strcpy(new_name + base_length + 1, new_ext);
    ((Internals*)file->internals)->name = new_name;
}

const char *virtual_file_get_name(VirtualFile *file)
{
    return ((Internals*)file->internals)->name;
}

bool virtual_file_set_name(VirtualFile *file, const char *new_name)
{
    char *name = ((Internals*)file->internals)->name;
    assert(file != nullptr);
    if (name != nullptr)
        delete []name;
    name = strdup(new_name);
    ((Internals*)file->internals)->name = name;
    return name != nullptr;
}
