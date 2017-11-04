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
(load #P "./unstd.lisp")
(load #P "./stdlib.lisp"))

(defvar *argc* nil)
(defvar *progname* nil)

(defmacro .mkargs. (&key argc not-implemented)
  ;; generate either *argc* or `(or)' for argv*
  (let ((ni (gensym "n-i")))
    `(let* ((,ni ,not-implemented)
            (%argv% (or #+abcl              ext:*command-line-argument-list*
                        #+allegro           (sys:command-line-arguments)
                        #+(or clasp ecl)    (loop for i from 0 below (si:argc)
                                                  collect (si:argv i))
                        #+clisp             *args*
                        #+clozure           ccl:*command-line-argument-list*
                        #+(or cmucl scl)    extensions:*command-line-strings*
                        #+gcl               si:*command-args*
                        #+(or genera mcl)   nil
                        #+lispworks         sys:*line-arguments-list*
                        #+mkcl              (loop for i from 0 below (mkcl:argc)
                                                  collect (mkcl:argv i))
                        #+sbcl              sb-ext:*posix-argv*
                        #+xcl               system:*argv*
                        #-(or abcl allegro clasp clisp clozure cmucl ecl gcl
                              genera lispworks mcl mkcl sbcl scl xcl)
                        (error 'not-implemented :proc (or ,not-implemented 'argv*)))))
       ,(if (not (null argc))
            `(setf *argc* (length %argv%))
            `%argv%))))

;; set *argc* according to current implementation of CL
(.mkargs. :argc t :not-implemented '*argc*)

(defun argv* (&optional .nth.)
  "returns either a list of args or a particular arg if .nth. is not null.
   calls `error' if something goes wrong."
  (let ((%argv% (.mkargs.)))
    (if (null .nth.)
        (if (< .nth. *argc*) ; make sure that we have enough args to get .nth. arg
            (nth .nth. %argv%))
        (error "argv*: position ~A is out of bounds: list has ~A ~A."
               (+ .nth. 1)
               *argc*
               (if (> *argc* 1) ; use position, if there is only 1, or positions.
                   "indices"
                   (if (< *argc* 1)
                       "indices"
                       "index"))))))

;(defun progname (&optional basename)
  ;(or #+abcl            nil
      ;#+allegro         nil
      ;#+(or clasp ecl)  (si:argv 0)

;;; Standard Streams
(defvar *stdin* *standard-input*)
(defvar *stdout* *standard-output*)
(defvar *stderr* *error-output*)

(setf *stdin*
      #.(or #+clozure         'ccl::*stdin*
            #+(or cmucl scl)  'system:*stdin*
            #+(or clasp ecl)  'ext:+process-standard-input+
            #+sbcl            'sb-sys:*stdin*
            '*stdin*))

(setf *stdout*
      #.(or #+clozure         'ccl::*stdout*
            #+(or cmucl scl)  'system:*stdout*
            #+(or clasp ecl)  'ext:+process-standard-output+
            #+sbcl            'sb-sys:*stdout*
            '*stdout*))

(setf *stderr*
      #.(or #+allegro         'excl::*stderr*
            #+clozure         'ccl::*stderr*
            #+(or cmucl scl)  'system:*stderr*
            #+(or clasp ecl)  'ext:+process-error-output+
            #+sbcl            'sb-sys:*stderr*
            '*stderr*))

;;; Safe Syntax
