
update main.dorfmitglied set einzug = 'false' where einzug is NULL;
update main.dorfmitglied set chaosnr = 0 where chaosnr is NULL;


/* Insert into member Active Member with Konto */
insert into chaosdorf.member ( 
memberId,
name,
firstname,
nickname,
email,
entryDate,
info,
reference,
street,
city,
zipCode,
collectionState,
state
)
select 
d.dorfmitglied_pkey,
d.name,
d.vorname,
d.nickname,
k.email,
d.eintrittsdatum,
d.info,
d.chaosnr,
a.strasse,
a.ort,
a.plz,
'K',
'A'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'false' AND
d.einzug = 'true';

/* Insert into member Active Member without Konto */
insert into chaosdorf.member ( 
memberId,
name,
firstname,
nickname,
email,
entryDate,
info,
reference,
street,
city,
zipCode,
collectionState,
state
)
select 
d.dorfmitglied_pkey,
d.name,
d.vorname,
d.nickname,
k.email,
d.eintrittsdatum,
d.info,
d.chaosnr,
a.strasse,
a.ort,
a.plz,
'N',
'A'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'false' AND
d.einzug = 'false';

/* Insert into member deleted Member without Konto */
insert into chaosdorf.member ( 
memberId,
name,
firstname,
nickname,
email,
entryDate,
info,
reference,
street,
city,
zipCode,
collectionState,
state
)
select 
d.dorfmitglied_pkey,
d.name,
d.vorname,
d.nickname,
k.email,
d.eintrittsdatum,
d.info,
d.chaosnr,
a.strasse,
a.ort,
a.plz,
'N',
'I'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'true' AND
d.einzug = 'false';

/* Insert into member deleted Member with Konto */
insert into chaosdorf.member ( 
memberId,
name,
firstname,
nickname,
email,
entryDate,
info,
reference,
street,
city,
zipCode,
collectionState,
state
)
select 
d.dorfmitglied_pkey,
d.name,
d.vorname,
d.nickname,
k.email,
d.eintrittsdatum,
d.info,
d.chaosnr,
a.strasse,
a.ort,
a.plz,
'K',
'I'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'true' AND
d.einzug = 'true';

/* Insert into member broken Member */
insert into chaosdorf.member ( 
memberId,
name,
firstname,
nickname,
email,
entryDate,
info,
reference,
street,
city,
zipCode,
collectionState,
state
)
select 
d.dorfmitglied_pkey,
d.name,
d.vorname,
d.nickname,
'-',
d.eintrittsdatum,
d.info,
d.chaosnr,
'-',
'-',
'-',
'N',
'I'
from main.dorfmitglied d
where 
dorfmitglied_pkey not in (select dorfmitglied_pkey from adresse) and
dorfmitglied_pkey not in (select dorfmitglied_pkey from kommunikation);



/* Update NULL to 0 */
update main.beitragstab set schulden = 0 where schulden is NULL;
update main.beitragstab set spende = 0 where spende is NULL;

/* insert into contribution */
insert into chaosdorf.contribution (
memberId,
fee,
additionalFee,
additionalDonation,
amortization,
donation,
validFrom,
info
)
select
b.dorfmitglied_pkey,
b.beitrag,
b.schulden,
0,
0,
b.spende,
b.gueltigab,
b.info
from main.beitragstab b;

/* Update NULL in 0 */
update main.saldo set konten = 0 where konten is NULL;

/* insert into balance */
insert into chaosdorf.balance (
memberId,
value,
valuta,
purpose,
account,
cashAccountId,
info
)
select
s.dorfmitglied_pkey,
s.betrag,
s.datum,
s.bezeichnung,
s.konten,
s.kasse_pkey,
s.info
from main.saldo s;

/* insert into bankAccount */
insert into bankaccount (
memberId,
name,
accountNumber,
code
)
select
k.dorfmitglied_pkey,
k.bank,
k.kontonr,
k.blz
from main.kontodaten k;

/* update NULL to - */
update main.kasse set buschl = '-' where buschl is NULL;

/* insert into cashaccount imported */
insert into chaosdorf.cashaccount (
cashAccountId,
primanota,
valuta,
date,
value,
transactionCode,
transactionText,
remoteName,
remoteBankCode,
remoteAccountNumber,
purpose,
memberId,
state
)
select
k.kasse_pkey,
k.einleseid,
k.valutadatum,
k.buchungsdatum,
k.betrag,
k.bankbuschl,
k.buschl,
k.fremdname,
k.fremdblz,
k.fremdktnr,
k.bezeichnung,
k.dorfmitglied_pkey,
'imported'
from main.kasse k
where
k.erfasst = 'false';

/* insert into cashaccount booked */
insert into chaosdorf.cashaccount (
cashAccountId,
primanota,
valuta,
date,
value,
transactionCode,
transactionText,
remoteName,
remoteBankCode,
remoteAccountNumber,
purpose,
memberId,
state
)
select
k.kasse_pkey,
k.einleseid,
k.valutadatum,
k.buchungsdatum,
k.betrag,
k.bankbuschl,
k.buschl,
k.fremdname,
k.fremdblz,
k.fremdktnr,
k.bezeichnung,
k.dorfmitglied_pkey,
'booked'
from main.kasse k
where
k.erfasst = 'true';

/* Some checks */
select (select count(dorfmitglied_pkey) from main.dorfmitglied) - (select count(memberId) from chaosdorf.member);
select (select count(dorfmitglied_pkey) from main.dorfmitglied where deleted = 'true') - (select count(memberId) from chaosdorf.member where state = 'I');
select (select count(dorfmitglied_pkey) from main.dorfmitglied where einzug = 'true') - (select count(memberId) from chaosdorf.member where collectionState = 'K');
select (select count(dorfmitglied_pkey) from main.dorfmitglied where deleted = 'false') - (select count(memberId) from chaosdorf.member where state = 'A');
select (select sum(dorfmitglied_pkey) from main.dorfmitglied) - (select sum(memberId) from chaosdorf.member);
select * from main.dorfmitglied m where m.dorfmitglied_pkey not in (select c.memberId from chaosdorf.member c);

select (select count(*) from main.beitragstab) - (select count(*) from chaosdorf.contribution);
select (select sum(beitrag) from main.beitragstab) - (select sum(fee) from chaosdorf.contribution);
select (select sum(spende) from main.beitragstab) - (select sum(donation) from chaosdorf.contribution);
select (select sum(schulden) from main.beitragstab) - (select sum(additionalFee) from chaosdorf.contribution);

select (select count(*) from main.kontodaten) - (select count(*) from chaosdorf.bankaccount);
select (select sum(dorfmitglied_pkey) from main.kontodaten) - (select sum(memberId) from chaosdorf.bankaccount);
select (select sum(kontonr) from main.kontodaten) - (select sum(accountNumber) from chaosdorf.bankaccount);
select (select sum(blz) from main.kontodaten) - (select sum(code) from chaosdorf.bankaccount);

select (select count(*) from main.saldo) - (select count(*) from chaosdorf.balance);
select (select sum(dorfmitglied_pkey) from main.saldo) - (select sum(memberId) from chaosdorf.balance);
select (select sum(betrag) from main.saldo) - (select sum(value) from chaosdorf.balance);
select (select sum(konten) from main.saldo) - (select sum(account) from chaosdorf.balance);

select (select count(*) from main.kasse) - (select count(*) from chaosdorf.cashaccount);
select (select sum(betrag) from main.kasse) - (select sum(value) from chaosdorf.cashaccount);
select (select count(*) from main.kasse where erfasst = 'true') - (select count(*) from chaosdorf.cashaccount where state = 'booked');
