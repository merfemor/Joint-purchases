if [ -x "$(which wine 2>/dev/null)" ]
then
	wine joint-purchases.exe 2>/dev/null;
else
	echo "\"wine\" package not found. Install \"wine\" and try again";
fi
