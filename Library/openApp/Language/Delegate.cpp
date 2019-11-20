/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Delegate
*/

#include <openApp/Language/Delegate.hpp>
#include <openApp/Core/Path.hpp>

oA::Lang::Delegate::Delegate(const oA::String &path, bool verbose)
    : Instantiator(verbose), _path(path)
{
}

oA::Item &oA::Lang::Delegate::instantiate(const ItemPtr &root)
{
    auto size = root->childCount();

    openFileContext(Path::GetCanonicalPath(_path));
    auto &ctx = context();
    ctx.root = root;
    ctx.target = root;
    processNode(*unit().tree);
    closeContext();
    if (root->childCount() != size + 1)
        throw LogicError("Delegate", "An error occured with instanciation of file @" + _path + "@");
    return root->getChild(size);
}