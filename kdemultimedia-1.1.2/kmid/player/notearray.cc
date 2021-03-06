/**************************************************************************

    notearray.cc  - NoteArray class, which holds an array of notes
    Copyright (C) 1998  Antonio Larrosa Jimenez

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    Send comments and bug fixes to antlarr@arrakis.es
    or to Antonio Larrosa, Rio Arnoya, 10 5B, 29006 Malaga, Spain

***************************************************************************/

#include "notearray.h"
#include <cstring>

NoteArray::NoteArray(void)
{
    totalAllocated=50;
    data=new noteCmd[totalAllocated];
    lastAdded=NULL;
}

NoteArray::~NoteArray()
{
    delete data;
    totalAllocated=0;
}

noteCmd *NoteArray::pointerTo(ulong pos)
{
    if (pos<totalAllocated) return &data[pos];
    while (pos>=totalAllocated)
    {
        noteCmd *tmp=new noteCmd[totalAllocated*2];
        memcpy(tmp,data,sizeof(noteCmd)*totalAllocated);
        delete data;
        data=tmp;
        totalAllocated*=2;
    }
    return &data[pos];
}

void NoteArray::at(ulong pos, ulong ms,int chn,int cmd,int note)
{
    noteCmd *tmp=pointerTo(pos);
    tmp->ms=ms;
    tmp->chn=chn;
    tmp->cmd=cmd;
    tmp->note=note;
}

void NoteArray::at(ulong pos, noteCmd s)
{
    noteCmd *tmp=pointerTo(pos);
    tmp->ms=s.ms;
    tmp->chn=s.chn;
    tmp->cmd=s.cmd;
    tmp->note=s.note;
}

noteCmd NoteArray::at(int pos)
{
    return *pointerTo(pos);
}

void NoteArray::add(ulong ms,int chn,int cmd,int note)
{
    if (lastAdded==NULL)
    {
        lastAdded=data;
        last=0;
    }
    else
    {
        last++;
        if (last==totalAllocated) lastAdded=pointerTo(totalAllocated);
        else lastAdded++;
    }
    lastAdded->ms=ms;
    lastAdded->chn=chn;
    lastAdded->cmd=cmd;
    lastAdded->note=note;
}

void NoteArray::next(void)
{
    if (it==lastAdded) {it=NULL;return;};
    it++;
}

void NoteArray::moveIteratorTo(ulong ms,int *pgm)
{
    noteCmd *ncmd;
    iteratorBegin();
    ncmd=get();
    int pgm2[16];
    for (int j=0;j<16;j++) pgm2[j]=0;
    while ((ncmd!=NULL)&&(ncmd->ms<ms))
    {
        if (ncmd->cmd==2) pgm2[ncmd->chn]=ncmd->note;
        next();
        ncmd=get();
    }
    if (pgm!=NULL)
    {
        for (int i=0;i<16;i++) pgm[i]=pgm2[i];
    }
}
