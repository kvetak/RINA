//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CONNECTIONTABLEENTRY_H_
#define CONNECTIONTABLEENTRY_H_

#include "APNamingInfo.h"

class ConnectionTableEntry {
  public:
    enum ConnectionStatus {UNKNOWN,
                           NIL,
                           FLOWPENDING,
                           CONNECTPENDING,
                           AUTHENTICATING,
                           ESTABLISHED,
                           RELEASING};

    //De-constructors
    ConnectionTableEntry();
    ConnectionTableEntry(APNamingInfo napni);
    virtual ~ConnectionTableEntry();

    std::string info() const;
    std::string getConnectionStatusString() const;

    //Getters and Setters
    const APNamingInfo& getApni() const;
    void setApni(const APNamingInfo& apni);
    void setConStatus(ConnectionStatus conStatus);

  private:
    APNamingInfo apni;
    ConnectionStatus conStatus;

};

//Free function
std::ostream& operator<< (std::ostream& os, const ConnectionTableEntry& cte);

#endif /* CONNECTIONTABLEENTRY_H_ */
