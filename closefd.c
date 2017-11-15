//  child process close fds inheritance in father  process

    struct rlimit    rl;
    
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
    {
        perror("getrlimit(RLIMIT_NOFILE, &rl)");
        return -1;
    }
    if(rl.rlim_max == RLIM_INFINITY)
    {
        rl.rlim_max = 1024;
    }
    for(i = 0; i < rl.rlim_max; i++)
    {
        close(i);
    }
