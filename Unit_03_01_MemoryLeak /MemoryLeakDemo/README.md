{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # Unit_03_01_MemoryLeak\
\
## How to Run\
- Open in Xcode.\
- **Fixed Mode**: Run \uc0\u9654  without arguments. Console shows `[FIXED MODE]`, memory is freed each second, Activity Monitor memory stays flat.\
- **Leak Mode**: Product \uc0\u8594  Scheme \u8594  Edit Scheme \u8594  Arguments \u8594  add `leak`. Console shows `[LEAK MODE]`, memory is held each second, Activity Monitor memory rises steadily.\
\
## How to Observe\
- Open **Activity Monitor** \uc0\u8594  Memory tab \u8594  search for `MemoryLeakDemo`.\
- Watch the "Memory" column:\
  - In **Fixed Mode**, usage stays almost constant.\
  - In **Leak Mode**, usage increases ~1 MB per second (or faster if chunk size is larger).\
\
## Notes\
- The line `delete[] chunk;` is what prevents leaks.  \
- If you comment it out, even fixed mode will leak.  \
- Video demonstration shows both modes side by side.\
}