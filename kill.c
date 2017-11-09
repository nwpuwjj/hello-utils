while (kill(restart_orig_pid, 0) != -1) {
            debug(LOG_INFO, "Waiting for parent PID %d to die before continuing loading", restart_orig_pid);
            sleep(1);
        }
        //sig:准备发送的信号代码，假如其值为0则没有任何信号送出，但是系统会执行错误检查，通常会利用sig值为0来检验某个进程是否仍在执行
        
