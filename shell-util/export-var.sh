#!/bin/bash

prepend()
{
    [ -d "$2" ] && eval $1=\"$2':'\$$1\" && export $1;
}

prepend wjj ~;
prepend wjj ~/wjj_samba;
echo $wjj;

