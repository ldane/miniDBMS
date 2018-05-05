BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=1;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=2;

UPDATE account
SET balance=balance+1
WHERE accountid=10;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=4;

UPDATE account
SET balance=balance-1
WHERE accountid=8;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=6;

UPDATE account
SET balance=balance+1
WHERE accountid=10;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=6;

UPDATE account
SET balance=balance+1
WHERE accountid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=7;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=6;

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=9;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=2;

UPDATE account
SET balance=balance+1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

UPDATE account
SET balance=balance+1
WHERE accountid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=10;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=4;

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE account
SET balance=balance+1
WHERE accountid=8;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=7;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE account
SET balance=balance+1
WHERE accountid=10;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=8;

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=1;

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

UPDATE account
SET balance=balance+1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=3;

UPDATE account
SET balance=balance-1
WHERE accountid=10;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=10;

UPDATE product
SET quantity=quantity-1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=7;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=3;

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE account
SET balance=balance-1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

UPDATE account
SET balance=balance+1
WHERE accountid=10;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=8;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE account
SET balance=balance+1
WHERE accountid=8;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance+1
WHERE accountid=7;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=4;

UPDATE account
SET balance=balance+1
WHERE accountid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=8;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=8;

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=2;

UPDATE account
SET balance=balance+1
WHERE accountid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=10;

UPDATE account
SET balance=balance-1
WHERE accountid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=7;

UPDATE account
SET balance=balance-1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=1;

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE account
SET balance=balance-1
WHERE accountid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=6;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=8;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=10;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=7;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=8;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=4;

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=8;

UPDATE product
SET quantity=quantity+1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=10;

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=5;

UPDATE account
SET balance=balance-1
WHERE accountid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=7;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=4;

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=2;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=10;

UPDATE account
SET balance=balance-1
WHERE accountid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE account
SET balance=balance+1
WHERE accountid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=9;

UPDATE account
SET balance=balance+1
WHERE accountid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=2;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=5;

UPDATE account
SET balance=balance+1
WHERE accountid=6;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=2;

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=9;

UPDATE account
SET balance=balance+1
WHERE accountid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=7;

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

UPDATE product
SET quantity=quantity-1
WHERE productid=1;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=5;

UPDATE product
SET quantity=quantity-1
WHERE productid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance+1
WHERE accountid=1;

UPDATE account
SET balance=balance-1
WHERE accountid=9;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE account
SET balance=balance-1
WHERE accountid=5;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=1;

UPDATE product
SET quantity=quantity+1
WHERE productid=4;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity-1
WHERE productid=4;

UPDATE account
SET balance=balance-1
WHERE accountid=3;

COMMIT;
END TRANSACTION;

BEGIN TRANSACTION

UPDATE product
SET quantity=quantity+1
WHERE productid=3;

UPDATE account
SET balance=balance-1
WHERE accountid=1;

COMMIT;
END TRANSACTION;

SELECT * FROM account;
SELECT * FROM product;