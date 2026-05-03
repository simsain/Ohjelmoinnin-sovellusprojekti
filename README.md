# Ohjelmoinnin-sovellusprojekti

3. Lisää tietokantaasi taulu nimeltä car, jossa int-tyyppinen perusavain ja tekstikentät branch ja 
model. Kopio taulun luomiseen kirjoittamasi SQL-koodi reposi README-tiedostoon.

		select database();
		use netdb;
		create table car(
		id int auto_increment primary key,
		branch varchar(30),
		model varchar(30)
		);

