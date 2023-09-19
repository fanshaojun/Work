void orgsStatement( string file )   // 把org里的内容按句子存储
{
    ifstream infile; 
    infile.open( file.data() );   //将文件流对象与文件连接起来 
    assert( infile.is_open() );   //若失败,则输出错误消息,并终止程序运行 
 
    char nowcur;
	string tempStatement="";
	Statement temp;
	int num1 = 0;
 
    infile >> noskipws;
 
    while ( !infile.eof() )
    {
        infile>>nowcur;
 
		if((( nowcur >='a' )&&( nowcur <='z' ))||(( nowcur >='A' )&&( nowcur <='Z' )))
		{
			tempStatement += nowcur;
 
		}else if(( nowcur =='.' )||( nowcur =='?' )||( nowcur =='!' ))
		{
			transform(tempStatement.begin(), tempStatement.end(), tempStatement.begin(), ::tolower);
			temp.nums = num1+1;
			temp.statement = tempStatement;
			orgStatement[orgnums] = temp;     //按每句子存储org的内容到orgStatement[]中
			num1 = 0;
			tempStatement = "";
			orgnums++;      //org文件的句子的个数
		}else    //匹配到空格
		{
			if( tempStatement=="" )
			{
				continue;
			}
			else if(tempStatement[tempStatement.size()==1?1:tempStatement.size()-1] != ' ')  //匹配到空格，当前句末不为空格，添加空格
			{
				tempStatement += " ";
				num1 += 1;    //单词个数加1
			}
		}
    }
    infile.close();             //关闭文件输入流 
}
