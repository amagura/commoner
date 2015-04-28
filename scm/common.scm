#|
Copyright 2015 Alexej Magura

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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
