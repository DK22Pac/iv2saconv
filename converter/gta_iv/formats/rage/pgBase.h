#pragma once
#include "datBase.h"
#include "pgPtr.h"
#include "BlockMap.h"

namespace rage {

class pgBase : public datBase {
private:
    pgPtr<BlockMap> m_blockMap;
};

}