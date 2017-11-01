/**
 *  function_name: calLanSpeed2
 *                calculate lan client network upload and download speed
 *                the rule will be written into FORWARD chain / filter table
 *			2017/9/28: wjj: seems iptables capture few packets, so use ebtables 
 */

void calLanSpeed2()
{
	DEBUG_PRINTF("=====[%s]======\n",__func__);
    system("ebtables -F Callanuploadspeed");
    system("ebtables -F Callandownloadspeed");
	int i=0;
	FILE *up=NULL;
    FILE *down=NULL;
	char str[LANHOST_MAXLINESIZE]={0};
	char cmd[256]={0};
    char tmp_char[64]={0};
	int tmp_int=0;
	
	for(i=0;i<lanHostEntryTableNum;i++)
    {
    	if(lanHostEntryTable[i].online != 0)
    	{
        	memset(cmd,0,256);
        	snprintf(cmd,256,"ebtables -A Callanuploadspeed -s %s",lanHostEntryTable[i].macaddr);
        	system(cmd);
        	memset(cmd,0,256);
        	snprintf(cmd,256,"ebtables -A Callandownloadspeed -d %s",lanHostEntryTable[i].macaddr);
        	system(cmd);
    	}
    }

	sleep(1);
	
	/*
	  Bridge table: filter

	  Bridge chain: INPUT, entries: 1, policy: ACCEPT
	  -s 4c:cc:6a:e3:5a:d5 -j CONTINUE , pcnt = 1805 -- bcnt = 17218
	*/

	
    system("ebtables -L Callanuploadspeed --Lc  | awk 'NR>3{printf $2 \" \" $12 \" \\n\"}' > /tmp/.lanuploadspeed");
    system("ebtables -L Callandownloadspeed --Lc | awk 'NR>3{printf $2 \" \" $12 \" \\n\"}' > /tmp/.landownloadspeed");

	up = fopen("/tmp/.lanuploadspeed","r");

	if( up == NULL)
    {
        printf("====ERROR!!!=== %s==== can't open lanuploadspeed file ",__func__);
        return;
    }
	
	i=0;
	while ( (fgets(str,LANHOST_MAXLINESIZE,up)) !=NULL )
    {
        DEBUG_PRINTF("==func: %s=====str====%s=====\n",__func__,str);
    	memset(tmp_char,0,sizeof(tmp_char));
        sscanf(str,"%s %d",tmp_char,&tmp_int);
    	
        for(i=0;i<lanHostEntryTableNum;i++)
        {
        	//if(strncmp(lanHostEntryTable[i].macaddr,tmp_char,strlen(tmp_char)) == 0)
            if( !(check_mac_match(lanHostEntryTable[i].macaddr,tmp_char)) )
            {
        		lanHostEntryTable[i].tx = tmp_int;
				break;
        	}
        }
		DEBUG_PRINTF("[%s]==i:%d===\n",__func__,i);
     
    }

	if(up)
	{	
		fclose(up);
	}

	
	down = fopen("/tmp/.landownloadspeed","r");

	if( down == NULL)
    {
        printf("====ERROR!!!=== %s==== can't open landownloadspeed file ",__func__);
        return;
    }
	
	i=0;
	while ( (fgets(str,LANHOST_MAXLINESIZE,down)) !=NULL )
    {
        DEBUG_PRINTF("==func: %s=====str====%s=====\n",__func__,str);
    	memset(tmp_char,0,sizeof(tmp_char));
        sscanf(str,"%s %d",tmp_char,&tmp_int);
    	
        for(i=0;i<lanHostEntryTableNum;i++)
        {
        	//if(strncmp(lanHostEntryTable[i].macaddr,tmp_char,strlen(tmp_char)) == 0)
        	if( !(check_mac_match(lanHostEntryTable[i].macaddr,tmp_char)) )
        	{
        		lanHostEntryTable[i].rx = tmp_int;
				break;
        	}
        }
		DEBUG_PRINTF("[%s]==i:%d===\n",__func__,i);
    }

	if(down)
	{	
		fclose(down);
	}
	

	for(i=0;i<lanHostEntryTableNum;i++)
    {
    	if(lanHostEntryTable[i].online != 0)
    	{
        	memset(cmd,0,256);
        	snprintf(cmd,256,"ebtables -D Callanuploadspeed -s %s",lanHostEntryTable[i].macaddr);
        	system(cmd);
        	memset(cmd,0,256);
        	snprintf(cmd,256,"ebtables -D Callandownloadspeed -d %s",lanHostEntryTable[i].macaddr);
        	system(cmd);
    	}
    }
    

}
