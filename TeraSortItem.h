#ifndef TERASORTITEM_H
#define TERASORTITEM_H
#include "defines.h"
#include "includes.h"

typedef struct
{
        uint8_t key[10];
        uint8_t b1[2];
        char rowid[32];
        uint8_t b2[4];
        uint8_t filler[48];
        uint8_t b3[4];
}teraitem_r;

class TeraSortItem {
  private:
    teraitem_r * teraitem;
    uint128_t key_value;
  public:
    TeraSortItem();
    TeraSortItem (TeraSortItem & teraSortItem);
    TeraSortItem (teraitem_r  * p_teraitem);
    void operator = (TeraSortItem * teraSortItem);
    uint128_t key ();
    void swap (TeraSortItem * p_teraSortItem);
    
    bool operator > (TeraSortItem * p_teraSortItem);
    bool operator < (TeraSortItem * p_teraSortItem);
    bool operator >= (TeraSortItem * p_teraSortItem);
    bool operator <= (TeraSortItem * p_teraSortItem);
    bool operator == (TeraSortItem * p_teraSortItem);
    bool operator != (TeraSortItem * p_teraSortItem);
    teraitem_r * getTeraItem ();
    void addToKeyValue(uint128_t p_key_value);
    uint128_t getKeyValue();    
    void keyValueAverage(uint16_t p_divisor);
    uint16_t hash(uint16_t p_reducers);
    ~TeraSortItem();
};


#endif