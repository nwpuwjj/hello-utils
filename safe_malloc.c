
/** Allocate zero-filled ram or die.
 * @param size Number of bytes to allocate
 * @return void * pointer to the zero'd bytes.
 */
void *
safe_malloc(size_t size)
{
    void *retval = NULL;
    retval = malloc(size);
    if (!retval) {
        debug(LOG_CRIT, "Failed to malloc %d bytes of memory: %s.  Bailing out", size, strerror(errno));
        exit(1);
    }
    memset(retval, 0, size);
    return (retval);
}

/** Re-allocates memory to a new larger allocation.
 * DOES NOT ZERO the added RAM
 * Original pointer is INVALID after call
 * Dies on allocation failures.
 * @param ptr A pointer to a current allocation from safe_malloc()
 * @param newsize What size it should now be in bytes
 * @return pointer to newly allocation ram
 */
void *
safe_realloc(void *ptr, size_t newsize)
{
    void *retval = NULL;
    retval = realloc(ptr, newsize);
    if (NULL == retval) {
        debug(LOG_CRIT, "Failed to realloc buffer to %d bytes of memory: %s. Bailing out", newsize, strerror(errno));
        exit(1);
    }
    return retval;
}
