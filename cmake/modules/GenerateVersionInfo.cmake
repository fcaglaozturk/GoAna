 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
 # Configure FairVersion.h
 # ------------------------------

 Find_Package(Git)

 If(GIT_FOUND AND EXISTS "${SOURCE_DIR}/.git")
   Execute_Process(COMMAND ${GIT_EXECUTABLE} describe
                   OUTPUT_VARIABLE GOANA_GIT_VERSION
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                   WORKING_DIRECTORY ${SOURCE_DIR}
                  )
   Execute_Process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd
                   OUTPUT_VARIABLE GOANA_GIT_DATE
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                   WORKING_DIRECTORY ${SOURCE_DIR}
                  )
   Message(STATUS "FairRoot Version - ${GOANA_GIT_VERSION} from - ${GOANA_GIT_DATE}")
   if(GOANA)
     Configure_File(${GOANA}/scripts/FairVersion.h.tmp ${BINARY_DIR}/FairVersion.h @ONLY)
   else(GOANA)  
     Configure_File(${SOURCE_DIR}/cmake/scripts/FairVersion.h.tmp ${BINARY_DIR}/FairVersion.h @ONLY)
   endif(GOANA)
  
 Else()
   if(GOANA)
     Configure_File(${GOANA}/scripts/FairVersion.h.default ${BINARY_DIR}/FairVersion.h COPYONLY)
   else(GOANA) 
     Configure_File(${SOURCE_DIR}/cmake/scripts/FairVersion.h.default ${BINARY_DIR}/FairVersion.h COPYONLY)
   endif(GOANA)
 EndIf()

