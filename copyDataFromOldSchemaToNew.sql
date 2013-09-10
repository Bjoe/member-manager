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
d.einzug = 'true' 

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
d.einzug = 'false' 

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
'D'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'true' AND
d.einzug = 'false' 

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
'D'
from main.dorfmitglied d, main.adresse a, main.kommunikation k 
where 
d.dorfmitglied_pkey = k.dorfmitglied_pkey AND
d.dorfmitglied_pkey = a.dorfmitglied_pkey AND
d.deleted = 'true' AND
d.einzug = 'true' 

/* Update NULL to 0 */
update main.beitragstab set schulden = 0 where schulden is NULL
update main.beitragstab set spende = 0 where spende is NULL

/* insert into contribution */
insert into chaosdorf.contribution (
memberId,
fee,
additionalFee,
donation,
validFrom,
info
)
select
b.dorfmitglied_pkey,
b.beitrag,
b.schulden,
b.spende,
b.gueltigab,
b.info
from main.beitragstab b

/* Update NULL in 0 */
update main.saldo set konten = 0 where konten is NULL

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
from main.saldo s

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
from main.kontodaten k

/* update NULL to - */
update main.kasse set buschl = '-' where buschl is NULL

/* insert into cashaccount */
insert into chaosdorf.cashaccount (
cashAccountId,
deleted,
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
booked
)
select
k.kasse_pkey,
k.deleted,
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
k.erfasst
from main.kasse k
