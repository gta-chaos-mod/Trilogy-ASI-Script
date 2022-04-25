#pragma once

using namespace plugin;

struct CShoppingItem
{
    int  textureName;
    int  unk;
    int  modelName;
    int  modelType;
    char gxtEntry[8];
};
static_assert (sizeof (CShoppingItem) == 24, "incorrect size");

struct CShopping
{
    static void LoadShop (const char *name);

    static void LoadShoppingType (const char *name);

    static int &m_nCurrentShoppingType;
    static int &m_nTotalItems;

    static CShoppingItem *m_aShoppingItems;
};