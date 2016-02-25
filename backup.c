/** backup.c
 *     cp1.c from understand Linux/Unix exercises modified
 *
 * Modified:  to take one argument the back up file at the CLI
   Change the name to .bak
 */
 #include       <sys/stat.h>
#include        <stdio.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <utime.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644

void oops(char *, char *);

main(int ac, char *av[])
{
        int     in_fd, out_fd, n_chars;
        char    buf[BUFFERSIZE];
		int pathLength = 100;
		struct stat info;
		struct utimbuf new_times;
						/* check args 	*/
        if ( ac != 2 ){
                fprintf( stderr, "usage: %s source destination\n", *av);
                exit(1);
        }
		
						/* open files	*/

        if ( (in_fd=open(av[1], O_RDONLY)) == -1 )
                oops("Cannot open ", av[1]);
			//create backup file add .bak
		char *backupFile = (char *) malloc(pathLength);
		strcpy(backupFile, av[1]);
		strcat(backupFile,".bak");
		
		

        if ( (out_fd=creat( backupFile, COPYMODE)) == -1 )
                oops( "Cannot creat", backupFile);
	
						/* copy files	*/

        while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 )
                if ( write( out_fd, buf, n_chars ) != n_chars )
                        oops("Write error to ", backupFile);
	if ( n_chars == -1 )
			oops("Read error from ", av[1]);
		
		
						/* modify access time */
		
		// time_t st_atime; /* time of last access */
        // time_t st_mtime; /* time of last modification */
		
		
		// modifiy access time and modification time to be the same as the original file
		
		if ( stat(av[1], &info) == -1 )		/* stat original	 */
			perror( av[1] );
		
		
		
		new_times.actime = info.st_atime;     // set time buffer to old file access time
		new_times.modtime = info.st_mtime;    // set time buffer to old file mod time
		
		
		if (utime(backupFile, &new_times) < 0)  //launch utime to update the backup with old mod and access times
			perror(backupFile);
		
		
		
						/* close files	*/

        if ( close(in_fd) == -1 || close(out_fd) == -1 )
                oops("Error closing files","");
}

void oops(char *s1, char *s2)
{
        fprintf(stderr,"Error: %s ", s1);
        perror(s2);
        exit(1);
}