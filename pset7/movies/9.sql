SELECT name FROM people WITH id IN (SELECT DISTINCT people.id FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id WHERE movies.year = '2004') ORDER BY people.birth;