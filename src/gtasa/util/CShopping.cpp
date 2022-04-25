#include "CShopping.h"

int &CShopping::m_nCurrentShoppingType = *(int *) 0xA9A7C8;
int &CShopping::m_nTotalItems          = *(int *) 0xA9A7CC;

CShoppingItem *CShopping::m_aShoppingItems = (CShoppingItem *) 0xA986F0;

void
CShopping::LoadShop (const char *name)
{
    Call<0x49BBE0> (name);
}

void
CShopping::LoadShoppingType (const char *name)
{
    Call<0x49B8D0> (name);
}