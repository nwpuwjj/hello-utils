
/** Sprintf into a newly allocated buffer
 * Memory MUST be freed. Dies if memory cannot be allocated.
 * @param strp Pointer to a pointer that will be set to the newly allocated string
 * @param fmt Format string like sprintf
 * @param ... Variable number of arguments for format string
 * @return int Size of allocated string.
 */
int
safe_asprintf(char **strp, const char *fmt, ...)
{
    va_list ap;
    int retval;

    va_start(ap, fmt);
    retval = safe_vasprintf(strp, fmt, ap);
    va_end(ap);

    return (retval);
}

/** Sprintf into a newly allocated buffer
 * Memory MUST be freed. Dies if memory cannot be allocted.
 * @param strp Pointer to a pointer that will be set to the newly allocated string
 * @param fmt Format string like sprintf
 * @param ap pre-digested va_list of arguments.
 * @return int Size of allocated string.
 */
int
safe_vasprintf(char **strp, const char *fmt, va_list ap)
{
    int retval;

    retval = vasprintf(strp, fmt, ap);

    if (retval == -1) {
        debug(LOG_CRIT, "Failed to vasprintf: %s.  Bailing out", strerror(errno));
        exit(1);
    }
    return (retval);
}
