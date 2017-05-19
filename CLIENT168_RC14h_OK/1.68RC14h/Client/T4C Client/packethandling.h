#ifndef PACKETHANDLING_H
#define PACKETHANDLING_H

// Include
#include "TFCPacket.h"

class PacketHandling {
// Class that take care of handling packet

   public:
      static void IndirectTalk(TFCPacket *);             // Type 27
      static void FromPreInGameToInGame(TFCPacket *);    // Type 46
      static void TeleportPlayer(TFCPacket *);           // Type 57
      static void SetUnitStat(TFCPacket *);              // Type 69

};

#endif