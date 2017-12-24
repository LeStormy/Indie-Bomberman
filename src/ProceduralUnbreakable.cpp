/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-26T11:58:41+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-05-26T11:58:54+02:00
 */
//
// Created by yan on 25/05/17.
//

#include "ProceduralGeneration.hpp"

void          ProceduralGeneration::generateModWUnbreakable(size_t lastHIndex, size_t lastWIndex)
{
    if (std::rand() % 2 == 0)
        setUnbreakable(lastHIndex, lastWIndex + 1);
    if (std::rand() % 2 == 0)
    {
        for (size_t cnt = lastWIndex; cnt < this->_width ; cnt++)
            if (cnt % 2 == 0)
                setUnbreakable(lastHIndex, cnt);
    }
    else
    {
        for (size_t cnt = lastWIndex + 1; cnt < this->_width ; cnt++)
            if (cnt % 2 == 0)
                setUnbreakable(lastHIndex, cnt);
    }
}

void          ProceduralGeneration::generateWUnbreakable(size_t lastHindex)
{
    size_t      lastWIndex = 0;

    if (this->_width % 2 == 0)
    {
        if (std::rand() % 2 == 0)
        {
            for (size_t cnt = 1; cnt < this->_width / 2; cnt++)
            {
                if (cnt % 2 != 0)
                {
                    setUnbreakable(lastHindex, cnt);
                    lastWIndex = cnt;
                }
            }
            generateModWUnbreakable(lastHindex, lastWIndex);
        }
        else
        {
            for (size_t idx = 1; idx < (this->_width / 2) ; idx++)
            {
                lastWIndex = idx;
                if (idx % 2 != 0)
                    setUnbreakable(lastHindex, idx);
            }
            generateModWUnbreakable(lastHindex, lastWIndex);
        }
    }
    else
        for (size_t cnt = 1; cnt < this->_width; cnt++)
            if (cnt % 2 != 0)
                setUnbreakable(lastHindex, cnt);
}

void          ProceduralGeneration::generateUnbreakable()
{
    size_t    lastHIndex = 0;

    if (this->_height % 2 == 0)
    {
        for (size_t cnt = 1; cnt < this->_height / 2; cnt++)
        {
            if (cnt % 2 != 0)
            {
                lastHIndex = cnt;
                generateWUnbreakable(cnt);
            }
        }
        for (size_t idx = lastHIndex; idx < this->_height; idx++)
        {
            if (idx % 2 == 0)
                generateWUnbreakable(idx);
        }
    }
    else
    {
        for (size_t cnt = 1; cnt < this->_height; cnt++)
        {
            if (cnt % 2 != 0)
                generateWUnbreakable(cnt);
        }
    }
}