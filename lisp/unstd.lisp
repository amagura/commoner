#|
Copyright (C) 2015-2019 Alexej G. Magura

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
;(defmacro STARTDIR (&optional subdir)
  ;(let ((%x% (gensym "%x%->subdir")))
    ;`(let ((,%x% ,subdir))
       ;(if (not (null ,%x%))
           ;(format nil "../~A" ,%x%)
           ;(STARTDIR "")))))

(load (format nil "~A/stdlib.lisp" (first (last (pathname-directory *load-truename*)))))

(dolist (try (list *load-truename*
               *load-pathname*
               *default-pathname-defaults*))
  (pprint try))

(defun STARTDIR (&optional subdir &key :as-macro)
  (let ((body '(if (not (null subdir))
                   ;; concatenate two strings, which represent filesystem locations
                   (format nil "../~A" subdir)
                   (STARTDIR ""))))
    (if (not (null as-macro))
        (macrolet ((STARTDIR (&optional subdir)
                     ,body))
          (STARTDIR subdir))
        (unquote body))))

(defun __asdf-version__ ()
  (when (find-package :asdf)
    (let ((ver (symbol-value
                 (or (find-symbol (string :*asdf-version*) :asdf)
                     (find-symbol (string :*asdf-revision*) :asdf)))))
      (etypecase ver
        (string ver)
        (cons (with-output-to-string (s)
                (loop for (n . m) on ver
                      do (princ n s)
                      (when m (princ "." s)))))
        (null "1.0")))))
