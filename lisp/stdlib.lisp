(defun odd (list)
  "returns the items appearing at odd indices within a list"
  (do ((l list (cddr l)))
      (x '() (cons (car l) x)))
  ((null l)
   (nreverse x)))
