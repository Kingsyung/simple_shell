#include "shell.h"

/**
 * myExit - exits the shell.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status.
 * (0) if shellInfo->argv[0] != "exit".
 */
int myExit(ShellInfo *shellInfo)
{
    int exitCheck;

    if (shellInfo->argv[1]) /* If there is an exit argument */
    {
        exitCheck = customAtoi(shellInfo->argv[1]);

        if (exitCheck == -1)
        {
            shellInfo->status = 2;
            printError(shellInfo, "Illegal number: ");
            _puts(shellInfo->argv[1]);  // Changed _eputs to _puts
            _putchar('\n');  // Changed _eputchar to _putchar
            return (1);
        }
        shellInfo->errorNumber = customAtoi(shellInfo->argv[1]);
        return (-2);
    }
    shellInfo->errorNumber = -1;
    return (-2);
}

/**
 * myCd - changes the current directory of the process.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myCd(ShellInfo *shellInfo)
{
    char *currentDir, *dir, buffer[1024];
    int chdirRet;

    currentDir = getcwd(buffer, 1024);

    if (!currentDir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!shellInfo->argv[1])
    {
        dir = getenv("HOME");

        if (!dir)
            chdirRet = chdir((dir = getenv("PWD")) ? dir : "/");
        else
            chdirRet = chdir(dir);
    }
    else if (_strcmp(shellInfo->argv[1], "-") == 0)
    {
        if (!getenv("OLDPWD"))
        {
            _puts(currentDir);
            _putchar('\n');
            return (1);
        }
        _puts(getenv("OLDPWD")), _putchar('\n');
        chdirRet = chdir((dir = getenv("OLDPWD")) ? dir : "/");
    }
    else
        chdirRet = chdir(shellInfo->argv[1]);

    if (chdirRet == -1)
    {
        printError(shellInfo, "can't cd to ");
        _puts(shellInfo->argv[1]), _putchar('\n');
    }
    else
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", getcwd(buffer, 1024), 1);
    }
    return (0);
}

/**
 * myHelp - changes the current directory of the process.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myHelp(ShellInfo *shellInfo)
{
    char **argArray;

    argArray = shellInfo->argv;
    _puts("help call works. Function not yet implemented \n");

    if (0)
        _puts(*argArray); /* temp att_unused workaround */
    return (0);
}
