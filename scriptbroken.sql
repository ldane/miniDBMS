BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid='6';

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=2;

COMMIT;
END TRANSACTION;

SELECT * FROM account;