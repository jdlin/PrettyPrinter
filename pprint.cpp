/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  PPRINT.C -- Source Code Identation                                 *
 *                                                                     *
 *  maintenance page                                                   *
 *                                                                     *
 *  Build Instructions:                                                *
 *                                                                     *
 *    bcc -ml -G pprint getline cmdline files tokens strings           *
 *                                                                     *
 *  Required compiler options settings:                                *
 *  - Borland includes some non-ANSI standard file and data            *
 *    declarations in their ANSI-standard header files.                *
 *    These are available only if compiled with menu option:           *
 *    Options|Compiler|Source|Borland C++ (default for bcc).           *
 *                                                                     *
 *  Language:        Borland C++, ver 3.1                              *
 *  Platform:        i386/40, DOS 5.0                                  *
 *  Author:          Jordon Lin                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "pprint.hpp"

//--------------------------------------------------------------------
//  Processing:
//    - indent the next line that followed the keyword
//  Return
//    - the next line
//--------------------------------------------------------------------
string indent_next(token &fp, pparm &pptr, string &comment)
{
        string line = "";
        int len = comment.length();

        if (fp.str[0] == '{')     //  keyword + comment + {
	{
            line += " {";         //
            if (len > 0)          // add comment after keyword
                line += comment;  // move comment after {, if any
            line += "\n";
//            line += indent_line(fp, pptr, 0);
	}
        else                      // keyword + comment\n +
        {                         //    single statement;
            string sta = fp.str;
	    if (fp.str[fp.str.length()-1] != ';')
            {
                string expr = indent_line(fp, pptr, 1); // get whole statement
                if (expr[0] != '(') sta += " ";
                sta += expr;
            }
            char c = get_ch(fp);          // read until \n
	    if  (c != '\n')
		put_ch(c);
	    else
		sta += "\n";
            if (len > 0)                  // add comment after keyword
                line += comment;
            string spaces(pptr.spaces()); // indent spaces
            line += "\n";                 // make a newline
            line += spaces;               // indent this single statement
	    line += sta;
            pptr.dec_level();             // decrease indent level
	}
        return line;
}
//--------------------------------------------------------------------
//  Processing:
//    - indentate this line that contains a keyword
//  Return
//    - the next line
//--------------------------------------------------------------------
string indent_keyword(token &fp, pparm &pptr)
{
    string line = "";
  
    pptr.inc_level();                    // increase indent level
    get_tok(fp);                         // get next token
    string comment = " ";
    if (fp.str[0] == '/')                // if the next token is comment
    {                                    // keyword + comments
        comment += fp.str;
        get_tok(fp);                     // get the next token
        line += indent_next(fp, pptr, comment); // recursive call
    }
    else if ( fp.str.match("if") || fp.str.match("for") ||
              fp.str.match("while") || fp.str.match("do") ||
              fp.str.match("switch") )   // keyword + keyword
    {
        for (int j = 0;j < fp.str.length(); j++)
            put_ch(fp.str[j]);
        line += "\n";                    // make a newline
        line += indent_line(fp, pptr, 0);// recursive call
        pptr.dec_level();                // decrease indent level
    }
    else                                 // keyword + general statement
    {
        comment = "";
        line += indent_next(fp, pptr, comment); // recursive call
    }

    return line;
}
  
//--------------------------------------------------------------------
//  Processing:
//    - read a line, then indent it
//  Return
//    - a indentated line
//--------------------------------------------------------------------
string indent_line(token &fp, pparm &pptr, int keyword)
{
    string line = "";
    int s;

    s = pptr.spaces();                    // current indent spaces
    line += get_line(fp, pptr.spaces() - pptr.get_indent()); // get a line
    int len = line.length();

    if (line[0] == '}')                   // closing brace precede
        s -= pptr.get_indent();           // decrease indent spaces
    string space(s);
    string line2 = "";
    if (line[0] != '/' && keyword == 0)   // if not comment & not followed keyword
        line2 += space;                   // indent this line
    if (line[len-1]  == '}' || line[len-1]  == '{')
    {
        if (line[len-1]  == '}')
          pptr.dec_level();               // decrease indent level
        else if (line[len-1] == '{')
             pptr.inc_level();            // increase indent level
        char ch;
        if ((ch = get_ch(fp)) != '\n')    // read until end of this line
        {
            put_ch(ch);
            line += " ";
            line += get_line(fp, pptr.spaces() - pptr.get_indent());
        }
        else
            line += "\n";
        line2 += line;                    // append this line
    }
    else if (line[len-1] != '\n')         // keyword
    {
        line2 += line;                    // append this line
        line2 += indent_keyword(fp, pptr);// deal with keyword
    }
    else
        line2 += line;                    // append this line

     return line2;
}
/*
   This is main program
*/
void main(int argc, char *argv[]) {
  
    struct file_info fi;
    int got_file, index = 0;
    FILE *fptr;
    pparm pptr(2);
    char ch = 'q';
  
    if (argc > 1) {  /* there are arguments on the command line    */
        char *arg;     /* points to memory allocated for argv[] */
 /* process all arguments on command line */
        while (index < argc-1) {
 /* parse each command line argument */
 /* for commands and filenames       */
            while(*(arg = parse_in_place(argv[index+1],argv[0], pptr)) != '\0')
                if (!iscmd(arg)) {    /* this is filename pattern */
                    got_file = 0;
                    while(get_file_info(arg,&fi)) {
                        got_file = 1;
                        if((fptr = fopen(fi.name,"r")) == NULL)
                            fprintf(stderr,"can't open file %s\n",fi.name);
                        else { /* indent file */
                            fprintf(stderr,"\nindenting file %s\n",fi.name);
                            fclose(fptr);
                            token tok(fi.name);
                            do
                            {
                                cout << indent_line(tok,pptr,0);
                                if (ch != 'q')
                                    if ((ch = getch()) == 'z')
                                        break;
                            }
                            while(!done(tok));
                        }
                    }
                    if (!got_file)
                        fprintf(stderr,"can't open file %s\n",arg);
                }
            index++;
        }
    }
    else  /* no arguments on command line so give usage message */
        parse_in_place("?",argv[0], pptr);
}
