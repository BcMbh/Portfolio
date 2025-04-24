using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformerCombat : MonoBehaviour
{
    public PlatformerPlayer player;
    public Rigidbody2D rb;
    public LayerMask enemyLayer;
    public Animator anim;

    public Transform attackPoint;
    public float attackRange = 0.5f;
    public int attackDamage;
    public int curDamage;
    public int damageMulti;
    public int damageLimit;
    public float knockForce;
    private bool isFalling = false;

    /*[Header("Projectile")]
    public Transform firePoint;
    public GameObject prefab;
    public float pSpeed;
    public int pdamage;
    private bool throwEnd;
    
    [Header("Reload")]
    public int maxAmmo;
    private int currentAmmo;
    public float reloadTime;
    private bool isReloading = false;*/

    void start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        player = GetComponent<PlatformerPlayer>();
        
        curDamage = attackDamage;
        /*currentAmmo = maxAmmo;*/
    }

    void Update()
    {
        //attackMulti
        if(rb.velocity.y < 0 && Input.GetButton("Fire3")){
            if(curDamage < damageLimit){
                curDamage += damageMulti;
            }
            isFalling = true;
        }if(player.isGrounded){
            curDamage = attackDamage;
            isFalling = false;
        }
        //Hit
        if(isFalling && Input.GetButton("Fire3")){
            GroundHit();
        }
        if(Input.GetButtonDown("Fire3")){
            AttackHit();
        }

        /*//throw
        if(Input.GetButtonDown("Fire2")){
            anim.SetTrigger("Throw");
        }

        //Reload
        if(isReloading)
        return;
        if(currentAmmo <= 0){
            StartCoroutine(Reload());
            return;
        }*/
    }

    void AttackHit()
    {
        Collider2D[] hitEnemies = Physics2D.OverlapCircleAll(attackPoint.position,attackRange,enemyLayer);
        foreach(Collider2D enemy in hitEnemies){
            enemy.GetComponent<enemyHealth>().TakeDamage(curDamage);
		}
    }

    void GroundHit()
    {
        Collider2D[] hitEnemies = Physics2D.OverlapCircleAll(attackPoint.position,attackRange,enemyLayer);
        foreach(Collider2D enemy in hitEnemies){
            enemy.GetComponent<enemyHealth>().TakeDamage(curDamage);

            Rigidbody2D rb = enemy.GetComponent<Rigidbody2D>();
            Vector2 direction = enemy.transform.position - transform.position;
            direction.y = 0;
            rb.AddForce(direction.normalized * knockForce, ForceMode2D.Impulse);
		}
    }

    void Knockback()
    {
        Collider2D[] hitEnemies = Physics2D.OverlapCircleAll(transform.position,attackRange,enemyLayer);
        foreach(Collider2D enemy in hitEnemies){
            Rigidbody2D rb = enemy.GetComponent<Rigidbody2D>();
            Vector2 direction = enemy.transform.position - transform.position;
            direction.y = 0;
            rb.AddForce(direction.normalized * knockForce, ForceMode2D.Impulse);
		}
    }
    
    /*void Throw()
    {
        GameObject projectile = Instantiate(prefab,firePoint.position,firePoint.rotation);
        projectile.GetComponent<Rigidbody2D>().velocity = transform.right * pSpeed;
        projectile.GetComponent<projectile>().damage = pdamage;

        currentAmmo--;
    }*/
    

    void OnDrawGizmosSelected()
    {
        if( attackPoint == null)
        return;
        Gizmos.DrawWireSphere(attackPoint.position,attackRange);
    }

    /*IEnumerator Reload()
    {
        isReloading = true;
        anim.SetBool("Reload",true);

        yield return new WaitForSeconds(reloadTime - .25f);
        anim.SetBool("Reload",false);
        yield return new WaitForSeconds(.25f);

        currentAmmo = maxAmmo;
        isReloading = false;
    }
    void OnEnable()
    {
        isReloading = false;
        anim.SetBool("Reload",false);
    }*/
    
}
