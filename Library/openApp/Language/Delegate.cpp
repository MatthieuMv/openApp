/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Delegate
*/

#include <openApp/Language/Delegate.hpp>
#include <openApp/Core/Path.hpp>

oA::Lang::Delegate::Delegate(bool verbose)
    : Instantiator(verbose)
{
}

oA::Item &oA::Lang::Delegate::instantiate(const ItemPtr &root, const String &path)
{
    auto size = root->childCount();

    if (!Path::Exists(path))
        throw AccessError("Delegate", "Can't process invalid file path @" + path + "@");
    openFileContext(Path::GetCanonicalPath(path));
    auto &ctx = context();
    ctx.root = root;
    ctx.target = root;
    processNode(*unit().tree);
    closeContext();
    if (root->childCount() != size + 1)
        throw LogicError("Delegate", "An error occured with instanciation of file @" + path + "@");
    return root->getChild(size);
}