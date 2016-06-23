/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  test_xml.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/21/2016 01:06:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <mxml.h>

int create_wx_xml()
{
    FILE *fp;

    mxml_node_t *xml;    
    mxml_node_t *account;  
    mxml_node_t *node;
    xml = mxmlNewXML("1.0");
    account = mxmlNewElement(xml, "account");
    node = mxmlNewElement(account, "appid");
    mxmlNewText(node, 0, "abcdefg");

    node = mxmlNewElement(account, "appsecret");
    mxmlNewText(node, 0, "1234567");
    node = mxmlNewElement(account, "key");
    mxmlNewText(node, 0, "test_key");
    node = mxmlNewElement(account, "notify_url");
    mxmlNewText(node, 0, "");
    node = mxmlNewElement(account, "sslkey_path");
    mxmlNewText(node, 0, "");
    node = mxmlNewElement(account, "curl_timeout");
    mxmlNewText(node, 0, "timeouraaa");

    fp = fopen("account.xml", "w");
    if (!fp)
    {
        mxmlSaveFile(xml, fp, NULL);
        fclose(fp);
    }
    mxmlDelete(xml);

    return 0;
}
int create_mxml()
{
    int i = 0;
    mxml_node_t *xml;    
    mxml_node_t *schedule;  
    mxml_node_t *record;  
    mxml_node_t *space;  
    mxml_node_t *node;
    xml = mxmlNewXML("1.0");
    schedule = mxmlNewElement(xml, "schedule");
    for(i=0;i<2;i++)
    {
        record = mxmlNewElement(schedule, "record");

        node = mxmlNewElement(record, "program_content");
        mxmlNewText(node, 0, "val4");
        node = mxmlNewElement(record, "from");
        mxmlNewText(node, 0, "val5");
        node = mxmlNewElement(record, "to");
        mxmlNewText(node, 0, "val6");
        node = mxmlNewElement(record, "mode");
        mxmlNewText(node, 0, "val6");
        node = mxmlNewElement(record, "frequency");
        mxmlNewText(node, 0, "val6");
        node = mxmlNewElement(record, "pre_set_from");
        mxmlNewText(node, 0, "val6");
    }
    space = mxmlNewElement(schedule, "space");

    node = mxmlNewElement(space, "FHD");
    mxmlNewText(node, 0, "val4");
    node = mxmlNewElement(space, "SHD");
    mxmlNewText(node, 0, "val5");
    node = mxmlNewElement(space, "MAC");
    mxmlNewText(node, 0, "1234567");//mac_address());

    FILE *fp;
    fp = fopen("filename.xml", "w");
    mxmlSaveFile(xml, fp, NULL);
    fclose(fp);
    mxmlDelete(xml);
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    create_wx_xml();
//    create_mxml();
#if 1
    FILE *fp;
    mxml_node_t *tree,*node;

    fp = fopen("filename1.xml", "r");
    tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
    fclose(fp);

    mxml_node_t *id,*password;

    node = mxmlFindElement(tree, tree, "account",NULL, NULL,MXML_DESCEND);

//    printf(" year:%s \n",mxmlElementGetAttr(node,"year"));
//    printf(" date:%s \n",mxmlElementGetAttr(node,"date"));
//    printf(" month:%s \n",mxmlElementGetAttr(node,"month"));



    id = mxmlFindElement(node, tree, "appid",NULL, NULL,MXML_DESCEND);
    printf("[%s}\n",id->child->value.text.string);

    password = mxmlFindElement(node, tree, "key",NULL, NULL,MXML_DESCEND);

    printf("[%s]\n",password->child->value.text.string);


    mxmlDelete(tree);
#endif
    return EXIT_SUCCESS;
}
