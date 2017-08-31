#include "accountDatabase.h"
#include "global.h"

accountDatabase* accountDatabase::m_instance=nullptr;

accountDatabase::accountDatabase()
{
}

accountDatabase* accountDatabase::instance()
{
	if(m_instance==nullptr)
	{
		m_instance=new accountDatabase();
	//	m_instance->initDatabase();
	//	m_instance->getAccount();
		return m_instance;
	}
	else
		return m_instance;
}

bool accountDatabase::initDatabase()
{
	//初始化数据库的library
	if (0 == mysql_library_init(0, NULL, NULL))
	{
		cout << "DataBase library init succeed!!" << endl;
	}
	else
	{
		cout << "Database library init failed!!" << endl;
		return false;
	}
	//初始化数据库accountdata
	if (NULL != mysql_init(&AccountData))
	{
		cout << "Database accountdata initialized successfully" << endl;
	}
	else
	{
		cout<< "Database accountdata iniitialized failed" << endl;
	}
	//数据库的选项设置，这边设置了字符集
	if (0 == mysql_options(&AccountData, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
		cout << "mysql_option() succeed!!" << endl;
	}
	else
	{
		cout << "mysql_option() failed!!" << endl;
		return false;
	}
	//数据库登录
	if (NULL != mysql_real_connect(&AccountData, "127.0.0.1", "root", "0921", "account_data", 0, NULL, 0))
	{
		cout << "Database login successfully！！" << endl;
	}
	else
	{
		mysql_error(&AccountData);
		cout << "Database login failed！！" << endl;
		return false;
	}
	return true;
}

bool accountDatabase::getAccount()
{
	string sqlstr;

	sqlstr = "SELECT * FROM account;";
	if (0 == mysql_query(&AccountData, sqlstr.c_str()))
	{
		MYSQL_RES *result = NULL;
		result = mysql_store_result(&AccountData);
		int rowCount = mysql_num_rows(result);

		//unsigned int colCount = mysql_num_fields(result);

		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row)
		{
			Account.insert({ row[0],row[1] });
			global::instance()->addUser(row[0]);
			row = mysql_fetch_row(result);
		}
		cout << "account data read successfully!!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

unordered_map<string, string> accountDatabase::showAccount()
{
	return Account;
}

bool accountDatabase::addAccount(string username, string password)
{
	//在map中添加用户
	Account.insert({ username,password });

	//在数据库account表中添加用户
	string sqlstr;
	sqlstr = "INSERT INTO account(username,password) VALUES(";
	sqlstr += "'"+username+"'";
	sqlstr += ",";
	sqlstr += "'"+password+"'";
	sqlstr += ");";
	
	if (0 == mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "add user: " << username << " successfully!!" << endl;
	}
	else
	{
		cout<< "add user: " << username << " failed!!" << endl;
		return false;
	}

	//添加用户的联系人列表
	sqlstr.clear();
	sqlstr = "CREATE TABLE friends_";
	sqlstr += username;
	sqlstr += " (friendname CHAR(20) PRIMARY KEY,remark CHAR(30),status SMALLINT(1));";

	if (0 == mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "add user: " << username << " chatlist successfully!!" << endl;
	}
	else
	{
		cout << "添加用户" << username << " chatlist failed!!" << endl;
		return false;
	}
	return true;

}

bool accountDatabase::deleteAccount(string username, string password)//注销一个账户
{
	//在map中删除用户
	if (Account.find(username) == Account.end())
	{
		cout << "no this user！！" << username << endl;
		return false;
	}
	if (Account.find(username)->second != password)
	{
		cout << "the passed is failed, the account can not be deleted'！！" << endl;
		return false;
	}
	Account.erase(username);

	//在数据库account表中删除用户
	string sqlstr;
	sqlstr = "DELETE FROM account WHERE username='";
	sqlstr += username;
	sqlstr += "';";

	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "delete user: " << username << " failed!!" << endl;
		return false;
	}

	//删除用户的联系人列表
	sqlstr.clear();
	sqlstr = "DROP TABLE friends_";
	sqlstr += username;
	sqlstr += " RESTRICT;";

	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "delete user: " << username << " chatlist failed!!" << endl;
		return false;
	}

	cout << "delete contact: " << username << " successfully" << endl;
	return true;


}

bool accountDatabase::addFriend(string username, string friendname)
{
	if (Account.find(friendname) == Account.end())
	{
		cout << "no tihs user" << friendname << endl;
		return false;
	}

	string sqlstr;
	sqlstr = "INSERT INTO friends_";
	sqlstr += username;
	sqlstr += "(friendname,remark,status) VALUES(";
	sqlstr += "'" + friendname + "','" + friendname + "',";
	sqlstr += "0);";
	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "添加联系人" << friendname << "进" << username << "联系人列表失败!!" << endl;
		return false;
	}
	
	sqlstr.clear();
	sqlstr = "INSERT INTO friends_";
	sqlstr += friendname;
	sqlstr += "(friendname,remark,status) VALUES(";
	sqlstr += "'" + username + "','" + username + "',";
	sqlstr += "0);";
	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "添加联系人" << username << "进" << friendname << "联系人列表失败!!" << endl;
		return false;
	}

	cout << "添加联系人成功!!" << endl;
	return true;
}

bool accountDatabase::deleteFriend(string username, string friendname)
{
	string sqlstr;
	sqlstr = "DELETE FROM friends_";
	sqlstr += username;
	sqlstr+=" WHERE friendname='";
	sqlstr += friendname;
	sqlstr += "';";
	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "删除联系人" << friendname << "从" << username << "联系人列表失败!!" << endl;
		return false;
	}

	sqlstr.clear();
	sqlstr = "DELETE FROM friends_";
	sqlstr += friendname;
	sqlstr += " WHERE friendname='";
	sqlstr += username;
	sqlstr += "';";
	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "删除联系人" << username << "从" << friendname << "联系人列表失败!!" << endl;
		return false;
	}
	cout << "删除联系人" << username << "从" << friendname << "联系人列表成功!!" << endl;
	return true;
}

unordered_map<string, friendData> accountDatabase::getFriends(string username)
{
	unordered_map<string, friendData> friendList;
	string sqlstr;

	sqlstr = "SELECT * FROM friends_";
	sqlstr += username + ";";


	if (0 == mysql_query(&AccountData, sqlstr.c_str()))
	{
		MYSQL_RES *result = NULL;
		result = mysql_store_result(&AccountData);
		int rowCount = mysql_num_rows(result);

		//unsigned int colCount = mysql_num_fields(result);

		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row)
		{
			friendList.insert({ row[0],friendData(row[0],row[1],strcmp(row[2],"0")) });
			row = mysql_fetch_row(result);
		}
		cout << "friendList数据读取成功!!" << endl;

	}
	else
	{
		cout << "读取联系人列表失败！！，返回为空" << endl;
	}

	return friendList;

}

bool accountDatabase::setFriendRemark(string username, string friendname, string remark)
{
	string sqlstr;

	sqlstr = "UPDATE friends_";
	sqlstr += username;
	sqlstr += " SET remark='";
	sqlstr += remark + "' WHERE friendname='";
	sqlstr += friendname + "';";

	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "修改联系人" << friendname << "备注到" << remark << "失败!!" << endl;
		return false;
	}
	cout << "修改联系人" << friendname << "备注到" << remark << "成功!!" << endl;
	return true;
}

bool accountDatabase::setStatus(string username, string friendname, bool status)
{
	string sqlstr;

	sqlstr = "UPDATE friends_";
	sqlstr += username;
	if (status)
	{
		sqlstr += " SET status=1 WHERE friendname='";
	}
	else
	{
		sqlstr += " SET status=0 WHERE friendname='";
	}
	sqlstr += friendname + "';";

	if (0 != mysql_query(&AccountData, sqlstr.c_str()))
	{
		cout << "修改联系人" << friendname <<  "状态失败!!" << endl;
		return false;
	}
	cout << "修改联系人" << friendname << "状态成功!!" << endl;
	return true;
}
