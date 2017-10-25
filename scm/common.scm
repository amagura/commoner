#|
Copyright (C) 2015, 2016, 2017 Alexej G. Magura

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
|#

(module common
(1+
 1-
 !*
 false?
 true?
 depth
 )
(import
  scheme
  chicken
  loop
  filepath
  data-structures
  ports
  posix
  )

(define (depth tree)
  (if (atom? tree)
      0
      (1+ (apply max (map depth tree)))))

(define (1+ n)
  (+ 1 n))

(define (1- n)
  (- 1 n))

(define (!* fn #!rest ...)
  (not (eval `(,fn ,@...))))

(define (false? exp)
  (not (and exp #t)))

(define (true? exp)
  (and exp #t))

(define

;; fat cat
(define (fcat dest-file #!rest src-files)
  (do ((srcs src-files (cdr srcs))
       (src (open-input-file (car srcs))
	    (and (close-input-port src)
		 (open-input-file (car srcs))))
       (dst (open-output-file dest-file))
       (fp (file-read (port->fileno src) 4096)
	   (file-read (port->fileno src) 4096))
       (dst (open-output-file dest-file)
	    (file-write (port->fileno dst)
			(car fp)
			(cadr fp))))
      ((null? srcs) (and (close-output-port dst)
			 (close-input-port src)
			 (void)))))
#|
(define (build-pathnames tree)
  (if (= (depth tree) 1)
      (map (lambda (x)
	     (let ((dir (car x)))
	       (files (cdr x)))
	     (map (lambda (file)
		    |#
)
