#include "provided.h"
#include "http.h"
#include <string>
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
	string text;
	if (!HTTP().get(url, text))
		return false;

	if (!Steg::hide(text, msg, host))
		return false;

	return true;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
	string text;
	if (!HTTP().get(url, text))
		return false;

	if (!Steg::reveal(text, msg))
		return false;

	return true;
}
